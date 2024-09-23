#include "search_path_gr_scene.h"

#include <QGraphicsSceneMouseEvent>

SearchPathGrScene::SearchPathGrScene(QObject* p) :
    QGraphicsScene(p)
{
    addItem(&_mapGrItem);

    _bfsWorker.moveToThread(&_bfsThread);
    connect(this, &SearchPathGrScene::startSearchPath, &_bfsWorker, &BreadthFirstSearchWorker::search, Qt::QueuedConnection);
    connect(this, &SearchPathGrScene::stopSearchPath, &_bfsWorker, &BreadthFirstSearchWorker::stop, Qt::QueuedConnection);
    connect(&_bfsWorker, &BreadthFirstSearchWorker::finished, this, &SearchPathGrScene::pathFinded, Qt::QueuedConnection);
    _bfsThread.start();

    _genMapWorker.moveToThread(&_genMapThread);
    connect(this, &SearchPathGrScene::startGenerateMap, &_genMapWorker, &GenerateMapWorker::generate, Qt::QueuedConnection);
    connect(this, &SearchPathGrScene::stopGenerateMap, &_genMapWorker, &GenerateMapWorker::stop, Qt::QueuedConnection);
    connect(&_genMapWorker, &GenerateMapWorker::finished, this, &SearchPathGrScene::mapGenerated, Qt::QueuedConnection);
    _genMapThread.start();
}

SearchPathGrScene::~SearchPathGrScene()
{
    emit stopSearchPath();
    emit stopGenerateMap();

    _bfsThread.quit();
    _genMapThread.quit();

    _bfsThread.wait();
    _genMapThread.wait();
}

void SearchPathGrScene::generateMap(qreal w, qreal h)
{
    emit stopGenerateMap();
    emit startGenerateMap(w, h);
}

void SearchPathGrScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setPoint(event->scenePos(), event->buttons());
}

void SearchPathGrScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setPoint(event->scenePos(), event->buttons());
}

void SearchPathGrScene::setPoint(QPointF pos, Qt::MouseButtons btn)
{
    pos = _mapGrItem.mapFromScene(pos);
    QPoint point = { static_cast<int>(pos.x()), static_cast<int>(pos.y()) }; // toPoint округляет не в меньшую сторону при > 0.5
    if (btn == Qt::LeftButton)
        setStart(point);
    else if (btn == Qt::RightButton)
        setEnd(point);
}

void SearchPathGrScene::setStart(QPoint start)
{
    if (_mapGrItem.boundingRect().toRect().contains(start) &&
            !_wallMap[start.y()][start.x()])
    {
        _start = start;
        _mapGrItem.setStart(_start.value());
        searchPath();
    }
}

void SearchPathGrScene::setEnd(QPoint end)
{
    if (_mapGrItem.boundingRect().toRect().contains(end) &&
            !_wallMap[end.y()][end.x()])
    {
        _end = end;
        _mapGrItem.setEnd(_end.value());
        searchPath();
    }
}

void SearchPathGrScene::resetPoints()
{
    _start.reset();
    _end.reset();
    _mapGrItem.reset();
}

void SearchPathGrScene::searchPath()
{
    if (_start && _end)
    {
        emit stopSearchPath();
        emit startSearchPath(_wallMap, _start.value(), _end.value());
    }
}

void SearchPathGrScene::fit()
{
    QRectF rect = itemsBoundingRect();
    setSceneRect(rect);
}

void SearchPathGrScene::mapGenerated(QVector<QVector<bool>> wallMap)
{
    _wallMap = wallMap;
    resetPoints();
    _mapGrItem.setMap(_wallMap);

    fit();
}

void SearchPathGrScene::pathFinded(QVector<QPoint> path)
{
    _mapGrItem.setPath(path);
}
