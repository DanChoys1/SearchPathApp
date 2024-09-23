#include "map_gr_item.h"

#include <QPainter>
#include <QPainterPath>

namespace
{
constexpr qreal BorderSize = 0.1;

const QColor StartPointColor    { Qt::green };
const QColor EndPointColor      { Qt::red };
const QColor PathColor          { Qt::yellow };
const QColor GridColor          { Qt::black };
const QColor WallColor          { Qt::black };
const QColor BackgroundColor    { Qt::transparent };
}

MapGrItem::MapGrItem(QGraphicsItem *p) :
    QGraphicsItem(p)
{}

QRectF MapGrItem::boundingRect() const
{
    return QRectF{ 0, 0, static_cast<qreal>(_size.width()), static_cast<qreal>(_size.height()) };
}

void MapGrItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(Qt::NoPen);
    painter->fillPath(_path, StartPointColor);

    if (_start)
    {
        painter->setBrush(PathColor);
        painter->drawRect(_start->x(), _start->y(), 1, 1);
    }
    if (_end)
    {
        painter->setBrush(EndPointColor);
        painter->drawRect(_end->x(), _end->y(), 1, 1);
    }

    painter->drawPixmap(0, 0, _mapImg);
}

void MapGrItem::setMap(const QVector<QVector<bool>>& map)
{
    _size.setHeight(map.size());
    if (map.size() > 0)
        _size.setWidth(map.first().size());

    _mapImg = QPixmap(_size*10);
    _mapImg.setDevicePixelRatio(10);
    _mapImg.fill(BackgroundColor);

    QPainter painter(&_mapImg);
    painter.setPen(Qt::NoPen);
    painter.setBrush(WallColor);
    for (int y = 0; y < _size.height(); ++y)
    {
        for (int x = 0; x < _size.width(); ++x)
        {
            if (map[y][x])
        {
                painter.drawRect(x, y, 1, 1);
            }
        }
    }

    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen{ GridColor, BorderSize });
    painter.drawRect(QRectF{ BorderSize/2, BorderSize/2, _size.width() - BorderSize, _size.height() - BorderSize });
    for (int y = 1; y < _size.height(); ++y)
    {
        painter.drawLine(0, y, _size.width(), y);
    }
    for (int x = 1; x < _size.width(); ++x)
    {
        painter.drawLine(x, 0, x, _size.height());
    }

    update();
}

void MapGrItem::setPath(const QVector<QPoint>& path)
{
    _path = QPainterPath();
    foreach (const auto& pos, path)
    {
        _path.addRect(pos.x(), pos.y(), 1, 1);
    }

    update();
}

void MapGrItem::setStart(QPoint start)
{
    _start = start;
    update();
}

void MapGrItem::setEnd(QPoint end)
{
    _end = end;
    update();
}

void MapGrItem::reset()
{
    _start.reset();
    _end.reset();
    _path = QPainterPath();
}
