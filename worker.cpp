#include "worker.h"

#include <QThread>
#include <QAbstractEventDispatcher>

Worker::Worker(QObject *parent)
    : QObject(parent)
{}

void Worker::pause()
{
    QAbstractEventDispatcher* dispatcher = QThread::currentThread()->eventDispatcher();
    if (dispatcher == nullptr)
        return;

    if (!isRunning())
        return;

    _state = Paused;
    while (isPaused())
    {
        dispatcher->processEvents(QEventLoop::WaitForMoreEvents);
    }
}

void Worker::resume()
{
    if (isPaused())
    {
        run();
    }
}

void Worker::stop()
{
    _state = Stoped;
}

void Worker::run()
{
    _state = Running;
}

bool Worker::tryRun()
{
    if (isRunning() || isPaused())
        return false;

    run();
    return true;
}

bool Worker::isRunning() const
{
    return _state == Running;
}

bool Worker::isPaused() const
{
    return _state == Paused;
}

bool Worker::isStoped() const
{
    return _state == Stoped;
}

bool Worker::isCanceled()
{
    QAbstractEventDispatcher* dispatcher = QThread::currentThread()->eventDispatcher();
    if (dispatcher != nullptr)
        dispatcher->processEvents(QEventLoop::AllEvents);

    return isStoped();
}
