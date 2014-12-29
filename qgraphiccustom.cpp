#include "qgraphiccustom.h"

QGraphicCustom::QGraphicCustom(QWidget *parent):QGraphicsView(parent)
{
    scene = new QSceneCustom(this);
    scene->setSceneRect(0,0,1,1);
    this->setScene(scene);
    //scene->addRect(-10,-10,20,20,QPen(),QBrush());
}

void QGraphicCustom::setBackground(QImage background){
    scene->addBackgroundImg(background);
}

void QGraphicCustom::updateSceneSize(int width, int height){
    scene->setSceneRect(0,0,width,height);
}

void QGraphicCustom::rectDraw(QPointF pt1,QPointF pt2){
    QPointF ptMin;
    QPointF ptMax;
    if(pt1.x()<pt2.x()){
        ptMin.setX(pt1.x());
        ptMax.setX(pt2.x());
    }
    else{
        ptMin.setX(pt2.x());
        ptMax.setX(pt1.x());
    }
    if(pt1.y()<pt2.y()){
        ptMin.setY(pt1.y());
        ptMax.setY(pt2.y());
    }
    else{
        ptMin.setY(pt2.y());
        ptMax.setY(pt1.y());
    }
    scene->removeItem(rect);
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::white);
    rect = (HighlightItem*)scene->addRect(ptMin.x(),ptMin.y(),ptMax.x()-ptMin.x(),ptMax.y()-ptMin.y(),pen,QBrush());
    scene->update();
}

void QGraphicCustom::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        //get x,y coordinate
        point1 = mapToScene(event->pos());
        //point1 = mapToGlobal(event->pos());
        rect = (HighlightItem*)scene->addRect(0,0,0,0,QPen(),QBrush());
        //set flag on press
        drawMode = onDRAW;
    }
    else if(event->button() == Qt::RightButton){
        //selectItem;
        point1 = mapToScene(event->pos());
        QTransform transform;
        rect = (HighlightItem*)scene->itemAt(point1,transform);
        if(rect!=0){
            scene->removeItem(rect);
            scene->update();
            rectList.removeOne(rect);
            qDebug()<<"# of Rects: "<<rectList.size();
        }
    }
}

void QGraphicCustom::mouseMoveEvent(QMouseEvent *event){
    if(drawMode==onDRAW){
        point2 = mapToScene(event->pos());
        rectDraw(point1,point2);
    }
}

void QGraphicCustom::mouseReleaseEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        if(drawMode==onDRAW){
            drawMode = offDRAW;
            rectList.append(rect);
        }
        qDebug()<<"# of Rects: "<<rectList.size();
        qDebug()<<"point 1: "<<(rectList.last()->rect()).topLeft().x()<<", "<<(rectList.last()->rect()).topLeft().y();
        //qDebug()<<"point1:("<<ptMin.x()<<","<<ptMin.y()<<")";
        //qDebug()<<"point2:("<<ptMax.x()<<","<<ptMax.y()<<")";
    }
}
