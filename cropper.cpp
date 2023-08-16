#include "cropper.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QPainterPath>

Cropper::Cropper(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    connect(this, &Cropper::x2Changed,this,&Cropper::onX2Changed);
    connect(this, &Cropper::y2Changed,this, &Cropper::onY2Changed);
}

int Cropper::x1() const
{
    return m_x1;
}

void Cropper::setX1(int newX1)
{
    if (m_x1 == newX1)
        return;
    m_x1 = newX1;
    emit x1Changed();
}

int Cropper::y1() const
{
    return m_y1;
}

void Cropper::setY1(int newY1)
{
    if (m_y1 == newY1)
        return;
    m_y1 = newY1;
    emit y1Changed();
}

int Cropper::x2() const
{
    return m_x2;
}

void Cropper::setX2(int newX2)
{
    if (m_x2 == newX2)
        return;
    m_x2 = newX2;
    emit x2Changed();
}

int Cropper::y2() const
{
    return m_y2;
}

void Cropper::setY2(int newY2)
{
    if (m_y2 == newY2)
        return;
    m_y2 = newY2;
    emit y2Changed();
}

void Cropper::onX2Changed()
{
    this->update();
}

void Cropper::onY2Changed()
{
    this->update();
}

void Cropper::paint(QPainter *painter)
{
    QBrush brush(QColor::fromRgb(0, 0, 0, 150));
    painter->setBrush(brush);
    painter->setPen(Qt::NoPen);

    QPainterPath path;
    path.setFillRule(Qt::OddEvenFill);
    path.moveTo(boundingRect().x(),boundingRect().y());
    path.lineTo(boundingRect().width(),0);
    path.lineTo(boundingRect().width(),boundingRect().height());
    path.lineTo(boundingRect().x(),boundingRect().height());
    path.lineTo(boundingRect().x(),boundingRect().y());


    path.moveTo(m_x2,m_y1);
    path.lineTo(m_x1,m_y1);
    path.lineTo(m_x1,m_y2);
    path.lineTo(m_x2,m_y2);
    path.lineTo(m_x2,m_y1);

    painter->drawPath(path);
}
