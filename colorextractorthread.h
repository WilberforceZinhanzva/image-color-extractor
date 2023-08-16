#ifndef COLOREXTRACTORTHREAD_H
#define COLOREXTRACTORTHREAD_H

#include <QThread>
#include <QPoint>

class ColorExtractorThread : public QThread
{
    Q_OBJECT
public:
    enum AlgorithmType{
      VCenter,HCenter,LeftDiagonal,RightDiagonal
    };
    Q_ENUM(AlgorithmType)
    explicit ColorExtractorThread(QObject *parent = nullptr);

    // QThread interface

protected:
    void run();


public slots:
    void extractColor(const QString &filePath , const int &imageWidth , const QPoint topLeft, const QPoint &bottomRight );
    void algorithmTypeChanged(const AlgorithmType & algorithmType);

signals:
    void colorExtracted(const QColor&);
    void colorExtractionFinished();




private:
    int m_imageWidth;
    QString m_filePath;
    QPoint m_topLeft;
    QPoint m_bottomRight;

    AlgorithmType m_algorithmType = AlgorithmType::VCenter;



    // Extraction Algorithms

    void vCenterAlgorithm(const QImage &image, const int & fullImageWidth,const QPoint &fullTopLeft, const QPoint &fullBottomRight);
    void hCenterAlgorithm(const QImage &image, const int & fullImageWidth,const QPoint &fullTopLeft, const QPoint &fullBottomRight);
    void topLeftDiagonalAlgorithm(const QImage &image, const int & fullImageWidth,const QPoint &fullTopLeft, const QPoint &fullBottomRight);
    void topRightDiagonalAlgorithm(const QImage &image, const int &fullImageWidth, const QPoint &fullTopLeft, const QPoint &fullBottomRight);
    void extractorAlgorithm(const QImage &image, const int &fullImageWidth,QList<QColor> &colorsList,QList<int> &colorCount,const int &i,const int &j);
};

#endif // COLOREXTRACTORTHREAD_H
