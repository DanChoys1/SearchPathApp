#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{ Q_OBJECT
public:
    Worker(QObject* parent = nullptr);

public slots:
    void pause();
    void resume();
    void stop();

protected:
    void run();
    bool tryRun();

    bool isRunning() const;
    bool isPaused() const;
    bool isStoped() const;

    bool isCanceled();

protected:
    enum State
    {
        Stoped,
        Running,
        Paused
    };

    State _state = Stoped;

};

#endif // WORKER_H
