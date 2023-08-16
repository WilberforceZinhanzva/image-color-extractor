#include "colorextractormodel.h"


ColorExtractorModel::ColorExtractorModel(QObject *parent) : QAbstractListModel(parent)
{
    m_colorExtractorThread = new ColorExtractorThread(this);
    connect(m_colorExtractorThread,&ColorExtractorThread::colorExtracted,this,&ColorExtractorModel::colorExtracted);
    connect(m_colorExtractorThread,&ColorExtractorThread::colorExtractionFinished,this,&ColorExtractorModel::colorExtractionFinished);

}

void ColorExtractorModel::startColorExtraction(const QString &imagePath, const int &imageWidth, const QPoint &topLeft, const QPoint &bottomRight)
{
    m_colorExtractorThread->extractColor(imagePath,imageWidth,topLeft,bottomRight);
}

void ColorExtractorModel::changeAlgorithm(const ColorExtractorThread::AlgorithmType &algorithmType)
{
    m_colorExtractorThread->algorithmTypeChanged(algorithmType);
}

void ColorExtractorModel::colorExtracted(const QColor &color)
{
    beginInsertRows(QModelIndex(),m_colors.size(),m_colors.size());
    QColor c = color;
    m_colors.push_back(c);
    endInsertRows();

}

int ColorExtractorModel::rowCount(const QModelIndex &parent) const
{
    return m_colors.size();

}

QVariant ColorExtractorModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();

    switch(role){
    case ColorRole:
        return m_colors.at(row);
    }
    return QVariant();
}

QHash<int, QByteArray> ColorExtractorModel::roleNames() const
{
    QHash<int,QByteArray> names;
    names.insert(ColorRole,"Color");
    return names;
}
