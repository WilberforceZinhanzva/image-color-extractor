#ifndef CROPPER_H
#define CROPPER_H

#include <QQuickPaintedItem>

class Cropper : public QQuickPaintedItem
{
    Q_OBJECT
public:
    Cropper(QQuickItem *parent = 0);


private:
    int m_x1, m_y1;
    int m_x2, m_y2;

    // QQuickPaintedItem interface
    Q_PROPERTY(int x1 READ x1 WRITE setX1 NOTIFY x1Changed FINAL)
    Q_PROPERTY(int y1 READ y1 WRITE setY1 NOTIFY y1Changed FINAL)
    Q_PROPERTY(int x2 READ x2 WRITE setX2 NOTIFY x2Changed FINAL)
    Q_PROPERTY(int y2 READ y2 WRITE setY2 NOTIFY y2Changed FINAL)

public:
    void paint(QPainter *painter);
    int x1() const;
    void setX1(int newX1);
    int y1() const;
    void setY1(int newY1);
    int x2() const;
    void setX2(int newX2);
    int y2() const;
    void setY2(int newY2);
signals:
    void x1Changed();
    void y1Changed();
    void x2Changed();
    void y2Changed();

private slots:
    void onX2Changed();
    void onY2Changed();
};

#endif // CROPPER_H
