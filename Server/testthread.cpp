#include "testthread.h"

TestThread::TestThread(qint64 num, MyServer *serv)
    :server(serv), num(num)
{
    tester = new Tester(1, num, num, num, server, "tests.txt");

    connect(tester, SIGNAL(errorOpenFile()), SIGNAL(errorOpenFile()));
    connect(tester, SIGNAL(successfulDone()), SIGNAL(successfulDone()));
    connect(tester, SIGNAL(errorOpenFile()), tester, SLOT(deleteLater()));
    connect(tester, SIGNAL(successfulDone()), tester, SLOT(deleteLater()));

    qRegisterMetaType<QVector<QVector<qint64> > >("QVector<QVector<qint64> >");

    connect(serv, SIGNAL(endMultiply(QVector<QVector<qint64> >)), tester, SLOT(slotParallelIterationDone(QVector<QVector<qint64> >)));
    tester->moveToThread(this);
}


void TestThread::run()
{
    tester->test();
}
