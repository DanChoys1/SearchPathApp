#ifndef BREADTHFIRSTSEARCHWORKER_H
#define BREADTHFIRSTSEARCHWORKER_H

#include "worker.h"

#include <QPoint>
#include <QVector>

class BreadthFirstSearchWorker : public Worker
{ Q_OBJECT
public:
    BreadthFirstSearchWorker(QObject* p = nullptr);

public slots:
    void search(const QVector<QVector<bool>> wallMap, QPoint start, QPoint end);

signals:
    void finished(QVector<QPoint> path);

private:
    void finish(QVector<QPoint> path);

};

#endif // BREADTHFIRSTSEARCHWORKER_H
