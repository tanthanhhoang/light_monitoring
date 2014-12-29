#include "qscenecustom.h"
#include <QDebug>
/*int i=0;
inline qreal round(qreal val, int step) {
   int tmp = int(val) + step /2;
   tmp -= tmp % step;
   return qreal(tmp);
}*/

QSceneCustom::QSceneCustom(QObject *parent)
{
}
void QSceneCustom::addBackgroundImg(QImage img){
    image=img;
}

void QSceneCustom::drawBackground(QPainter *painter, const QRectF &rect){
    //i++;
    /*int step = 30;
       painter->setPen(QPen(QColor(200, 200, 255, 125)));
       // draw horizontal grid
       qreal start = round(rect.top(), step);
       if (start > rect.top()) {
          start -= step;
       }
       for (qreal y = start - step; y < rect.bottom(); ) {
          y += step;
          painter->drawLine(rect.left(), y, rect.right(), y);
       }
       // now draw vertical grid
       start = round(rect.left(), step);
       if (start > rect.left()) {
          start -= step;
       }
       for (qreal x = start - step; x < rect.right(); ) {
          x += step;
          painter->drawLine(x, rect.top(), x, rect.bottom());
       }*/
    //qDebug()<<i;
    painter->drawImage(0,0,image);
}
