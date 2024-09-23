#include "breadth_first_search_worker.h"

#include <QQueue>

namespace
{
    const std::array<QPoint, 4> Directions { QPoint{0, 1}, QPoint{1, 0}, QPoint{0, -1}, QPoint{-1, 0} };
}

BreadthFirstSearchWorker::BreadthFirstSearchWorker(QObject *p) :
    Worker(p)
{}

void BreadthFirstSearchWorker::search(const QVector<QVector<bool>> wallMap, QPoint start, QPoint end)
{
    if (!tryRun())
        return;

    if (wallMap.isEmpty() || wallMap[start.y()][start.x()] || wallMap[end.y()][end.x()])
        finish({});

    QQueue<QPoint> queue;
    queue.enqueue(start);

    QVector<QVector<bool>> _visited(wallMap.size(), QVector<bool>(wallMap.first().size(), false));
    _visited[start.y()][start.x()] = true;

    QVector<QVector<QPoint>> _parent(wallMap.size(), QVector<QPoint>(wallMap.first().size(), QPoint{ -1, -1 }));
    QPoint current{ -1,-1 };
    while (!queue.empty())
    {
        current = queue.dequeue();
        if (current == end)
            break;

        for (const QPoint& direction : Directions)
        {
            QPoint neighbor = current + direction;
            if (neighbor.y() >= 0 && neighbor.y() < wallMap.size() &&
                    neighbor.x() >= 0 && neighbor.x() < wallMap[0].size() &&
                    !_visited[neighbor.y()][neighbor.x()] && wallMap[neighbor.y()][neighbor.x()] == false)
            {
                queue.enqueue(neighbor);
                _visited[neighbor.y()][neighbor.x()] = true;
                _parent[neighbor.y()][neighbor.x()] = current;
            }
        }

        if (isCanceled())
            return;
    }

    if (current != end)
        finish({});

    QVector<QPoint> path;
    for (QPoint p = end; p != QPoint(-1, -1); p = _parent[p.y()][p.x()])
    {
        path.append(p);

        if (isCanceled())
            return;
    }
    std::reverse(path.begin(), path.end());

    finish(path);
}

void BreadthFirstSearchWorker::finish(QVector<QPoint> path)
{
    stop();
    emit finished(path);
}
