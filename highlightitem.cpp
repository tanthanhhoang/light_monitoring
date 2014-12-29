#include "highlightitem.h"

HighlightItem::HighlightItem()
{
    setAcceptHoverEvents(true);
    m_pen = new QPen();
}
void HighlightItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    m_pen->setColor(Qt::red);
    //this->pen(m_pen);
    update();
}
void HighlightItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    m_pen->setColor(Qt::black);
    //this->pen(m_pen);
    update();
}
//void HighlightItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    //painter->setPen(m_pen);
    //painter->drawRect(rect());
//}
