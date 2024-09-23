#ifndef MAPGRITEM_H
#define MAPGRITEM_H

#include <QGraphicsRectItem>

class MapGrItem : public QGraphicsItem
{
public:
    MapGrItem(QGraphicsItem* p = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;

    void setMap(const QVector<QVector<bool>>& map);
    void setPath(const QVector<QPoint>& path);

    void setStart(QPoint start);
    void setEnd(QPoint end);

    void reset();

private:
    QSize _size;

    QPixmap _mapImg;
    QPainterPath _path;

    std::optional<QPoint> _start;
    std::optional<QPoint> _end;

};

#endif // MAPGRITEM_H
