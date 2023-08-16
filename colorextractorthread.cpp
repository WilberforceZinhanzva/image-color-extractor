#include "colorextractorthread.h"
#include <QDebug>
#include <QImage>

ColorExtractorThread::ColorExtractorThread(QObject *parent)
    : QThread{parent}
{

}

void ColorExtractorThread::run()
{
    qDebug() << "Running Color Extractor Thread";

    QImage image(m_filePath);

    int fullImageWidth = image.width();
    int fullImageHeight = image.height();
    int selectionHeight = (fullImageHeight*m_imageWidth)/fullImageWidth;

    QPoint fullTopLeft;
    fullTopLeft.setX(fullImageWidth/m_imageWidth * m_topLeft.x());
    fullTopLeft.setY(fullImageHeight/selectionHeight * m_topLeft.y());

    QPoint fullBottomRight;
    fullBottomRight.setX(fullImageWidth/m_imageWidth * m_bottomRight.x());
    fullBottomRight.setY(fullImageHeight/selectionHeight * m_bottomRight.y());




    switch(m_algorithmType){
    case VCenter:
        vCenterAlgorithm(image,fullImageWidth,fullTopLeft,fullBottomRight);
        break;
    case HCenter:
        hCenterAlgorithm(image,fullImageWidth,fullTopLeft,fullBottomRight);
        break;
    case LeftDiagonal:
        topLeftDiagonalAlgorithm(image,fullImageWidth,fullTopLeft,fullBottomRight);
        break;
    case RightDiagonal:
        topRightDiagonalAlgorithm(image,fullImageWidth,fullTopLeft,fullBottomRight);
        break;
    default:
        vCenterAlgorithm(image,fullImageWidth,fullTopLeft,fullBottomRight);
    }
}

void ColorExtractorThread::extractColor(const QString &filePath, const int &imageWidth, const QPoint topLeft, const QPoint &bottomRight)
{

    if(this->isRunning()){
        qDebug() << "Thread currently running";
        return;
    }
    m_filePath = filePath.startsWith("file:///") ? filePath.sliced(8) : filePath;
    m_imageWidth = imageWidth;
    m_topLeft = topLeft;
    m_bottomRight = bottomRight;

    this->start();

    qDebug() << "Started Thread";

}

void ColorExtractorThread::algorithmTypeChanged(const AlgorithmType &algorithmType)
{
    if(m_algorithmType == algorithmType)
        return;

    m_algorithmType = algorithmType;
    qDebug() << "AlgorithmType changed";

}




void ColorExtractorThread::vCenterAlgorithm(const QImage &image, const int & fullImageWidth,const QPoint &fullTopLeft, const QPoint &fullBottomRight)
{
    //VCenter Algorithm
    QList<QColor> colorsList;
    QList<int> colorCount;

    int verticalMid = fullTopLeft.x() + (fullBottomRight.x() - fullTopLeft.x())/2;
    qDebug() << "Vertical Mid " << verticalMid;

    for(int j = fullTopLeft.y(); j < fullBottomRight.y(); j++){
        extractorAlgorithm(image,fullImageWidth,colorsList,colorCount,verticalMid,j);

    }

    for(int i = 0; i < colorCount.size(); i++){
        if(colorCount[i] > 10){
            emit colorExtracted(colorsList[i]);
        }
        emit colorExtracted(colorsList[i]);
    }

    qDebug() << "Finished running thread";
    emit colorExtractionFinished();


}

void ColorExtractorThread::hCenterAlgorithm(const QImage &image, const int &fullImageWidth, const QPoint &fullTopLeft, const QPoint &fullBottomRight)
{
    //HCenter Algorithm
    QList<QColor> colorsList;
    QList<int> colorCount;

    //int horizontalMid = fullTopLeft.x() + (fullBottomRight.x() - fullTopLeft.x())/2;
    int horizontalMid = fullTopLeft.y() + (fullBottomRight.y()-fullTopLeft.y())/2;


    for(int j = fullTopLeft.x(); j < fullBottomRight.x(); j++){
        extractorAlgorithm(image,fullImageWidth,colorsList,colorCount,j,horizontalMid);
    }

    for(int i = 0; i < colorCount.size(); i++){
        if(colorCount[i] > 10){
            emit colorExtracted(colorsList[i]);
        }
        emit colorExtracted(colorsList[i]);
    }

    qDebug() << "Finished running thread";
    emit colorExtractionFinished();

}

void ColorExtractorThread::topLeftDiagonalAlgorithm(const QImage &image, const int &fullImageWidth, const QPoint &fullTopLeft, const QPoint &fullBottomRight)
{
    //TLeft Diagonal Agorithm
    QList<QColor> colorsList;
    QList<int> colorCount;

    int x1 = fullTopLeft.x();
    int y1 = fullTopLeft.y();
    int x2 = fullBottomRight.x();
    int y2 = fullBottomRight.y();

    int slope = (y2 - y1)/(x2 - x1);
    int b = y1 -(slope * x1);

    for(int i = x1; i < x2; i++){
        int j = (slope * i) + b;

        extractorAlgorithm(image,fullImageWidth,colorsList,colorCount,i,j);

    }


    for(int i = 0; i < colorCount.size(); i++){
        if(colorCount[i] > 10){
            emit colorExtracted(colorsList[i]);
        }
        emit colorExtracted(colorsList[i]);
    }

    qDebug() << "Finished running thread";
    emit colorExtractionFinished();

}

void ColorExtractorThread::topRightDiagonalAlgorithm(const QImage &image, const int &fullImageWidth, const QPoint &fullTopLeft, const QPoint &fullBottomRight)
{
    //TRight Diagonal Algorithm
    QList<QColor> colorsList;
    QList<int> colorCount;

    int x1 = fullBottomRight.x();
    int y1 = fullTopLeft.y();
    int x2 = fullTopLeft.x();
    int y2 = fullBottomRight.y();

    int slope = (y2 - y1)/(x2 - x1);
    int b = y1 -(slope * x1);

    for(int i = x2; i < x1; i++){
        int j = (slope * i) + b;

        extractorAlgorithm(image,fullImageWidth,colorsList,colorCount,i,j);
    }

    for(int i = 0; i < colorCount.size(); i++){
        if(colorCount[i] > 10){
            emit colorExtracted(colorsList[i]);
        }
        emit colorExtracted(colorsList[i]);
    }

    qDebug() << "Finished running thread";
    emit colorExtractionFinished();

}

void ColorExtractorThread::extractorAlgorithm(const QImage &image, const int &fullImageWidth,QList<QColor> &colorsList,QList<int> &colorCount,const int &i,const int &j)
{
    QColor color = image.pixelColor(fullImageWidth/2,j);
    //qDebug() << color;
    if(colorsList.size()==0){
        colorsList.push_back(color);
        colorCount.push_back(1);
    }else{

        bool newColorHasZero = color.red() * color.green() * color.blue() == 0;
        bool lastColorHasZero =colorsList.last().red() * colorsList.last().green() * colorsList.last().blue() == 0;

        if(newColorHasZero||lastColorHasZero ){
            colorsList.push_back(color);
            colorCount.push_back(1);
        }else{
            int redRatio = colorsList.last().red()/ color.red();
            int greenRatio = colorsList.last().green()/ color.green();
            int blueRatio = colorsList.last().blue() / color.blue();

            if(redRatio == greenRatio && greenRatio == blueRatio){

                colorCount[colorCount.size()-1]+=1;
            }else{
                colorsList.push_back(color);
                colorCount.push_back(1);
            }
        }

    }

}
