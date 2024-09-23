#include "generate_map_worker.h"

#include <QRandomGenerator>

namespace
{
constexpr int WallOccupancyPercent = 20;
}

GenerateMapWorker::GenerateMapWorker(QObject *p) :
    Worker(p)
{}

void GenerateMapWorker::generate(int w, int h)
{
    if (!tryRun())
        return;

    QVector<QVector<bool>> wallMap(h);
    for (int i = 0; i < h; ++i)
    {
        wallMap[i].resize(w);
        for (int j = 0; j < w; ++j)
        {
            wallMap[i][j] = QRandomGenerator().global()->bounded(100) < WallOccupancyPercent;
            if (isCanceled())
                return;
        }
    }

    stop();
    emit finished(wallMap);
}
