#ifndef GENERATEMAPWORKER_H
#define GENERATEMAPWORKER_H

#include "worker.h"

class GenerateMapWorker : public Worker
{ Q_OBJECT
public:
    GenerateMapWorker(QObject* p = nullptr);

public slots:
    void generate(int w, int h);

signals:
    void finished(QVector<QVector<bool>> wallMap);

};

#endif // GENERATEMAPWORKER_H
