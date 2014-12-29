#ifndef QSCENECUSTOM_H
#define QSCENECUSTOM_H

#include <QGraphicsScene>
#include <QImage>
#include <QPainter>

class QSceneCustom:public QGraphicsScene
{
    Q_OBJECT
public:
    explicit QSceneCustom(QObject *parent);
    void addBackgroundImg(QImage img);
protected:
    void drawBackground( QPainter * painter, const QRectF & rect );
private:
    QImage image;
};

#endif // QSCENECUSTOM_H
