#ifndef SEARCHPATHGRSCENE_H
#define SEARCHPATHGRSCENE_H

#include "breadth_first_search_worker.h"
#include "generate_map_worker.h"
#include "map_gr_item.h"

#include <QGraphicsScene>
#include <QThread>

class SearchPathGrScene : public QGraphicsScene
{ Q_OBJECT
public:
    SearchPathGrScene(QObject* p = nullptr);
    ~SearchPathGrScene();

    void generateMap(qreal w, qreal h);

signals:
    void stopSearchPath();
    void startSearchPath(const QVector<QVector<bool>> wallMap, QPoint start, QPoint end);

    void stopGenerateMap();
    void startGenerateMap(int w, int h);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void setPoint(QPointF pos, Qt::MouseButtons btn);
    void setStart(QPoint start);
    void setEnd(QPoint end);

    void resetPoints();

    void searchPath();

    void fit();

private slots:
    void mapGenerated(QVector<QVector<bool>> wallMap);
    void pathFinded(QVector<QPoint> path);

private:
    MapGrItem _mapGrItem;
    BreadthFirstSearchWorker _bfsWorker;
    GenerateMapWorker _genMapWorker;

    QThread _genMapThread;
    QThread _bfsThread;

    QVector<QVector<bool>> _wallMap;
    std::optional<QPoint> _start;
    std::optional<QPoint> _end;

};

#endif // SEARCHPATHGRSCENE_H
