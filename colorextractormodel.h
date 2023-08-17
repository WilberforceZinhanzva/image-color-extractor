#ifndef COLOREXTRACTORMODEL_H
#define COLOREXTRACTORMODEL_H

#include <QAbstractListModel>
#include <QColor>
#include "colorextractorthread.h"



class ColorExtractorModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum ExtractorRoles{
        ColorRole = Qt::UserRole + 1
    };
    ColorExtractorModel(QObject * parent =0);

    Q_INVOKABLE void startColorExtraction(const QString &imagePath, const int &imageWidth, const QPoint &topLeft, const QPoint &bottomRight);
    Q_INVOKABLE void changeAlgorithm(const ColorExtractorThread::AlgorithmType &algorithmType);

    void clearColors();


private slots:
    void colorExtracted(const QColor & color);


signals:
    void colorExtractionFinished();


private:
    ColorExtractorThread *m_colorExtractorThread;
    QList<QColor> m_colors;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
};

#endif // COLOREXTRACTORMODEL_H
