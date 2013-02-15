#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QThread>

#include "tester.h"
#include "mainwindow.h"

class TestThread : public QThread
{
    Q_OBJECT
private:
    MyServer *server;
    qint64 num;
    Tester *tester;

protected:
    void run();

public:
    explicit TestThread(qint64 num, MyServer *server);
    
signals:
    void successfulDone();
    void errorOpenFile();

public slots:
    
};

#endif // TESTTHREAD_H
