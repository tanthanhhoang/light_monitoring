#ifndef HIGHLIGHTITEM_H
#define HIGHLIGHTITEM_H
#include <QGraphicsRectItem>
#include <QPen>
class HighlightItem:public QGraphicsRectItem
{
public:
    HighlightItem();
public slots:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPen* m_pen;
};

#endif // HIGHLIGHTITEM_H
