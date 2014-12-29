#ifndef QGRAPHICCUSTOM_H
#define QGRAPHICCUSTOM_H

#include <QGraphicsView>
#include "qscenecustom.h"
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QPointF>
#include <QRectF>
#include <QDebug>
#include <QList>
#include "highlightitem.h"

#define onDRAW   0
#define offDRAW  1

class QGraphicCustom : public QGraphicsView
{   
    Q_OBJECT
public:
    explicit QGraphicCustom(QWidget *parent = 0);
    void setBackground(QImage background);
    void updateSceneSize(int width, int height);
    QList<HighlightItem*> rectList;

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void rectDraw(QPointF pt1,QPointF pt2);
    int drawMode;
    QSceneCustom* scene;
    QPainter* painter;
    QPointF point1;
    QPointF point2;

    HighlightItem* rect;
};

#endif // QGRAPHICCUSTOM_H
