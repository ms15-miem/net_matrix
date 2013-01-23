#include "tester.h"
#include <ctime>

Tester::Tester(uint cycles, uint N1, uint N2, uint N3, MyServer *myServer, QString fileName, QObject *parent) :
    QObject(parent), N1(N1), N2(N2), N3(N3), cycles(cycles), myServer(myServer), fileName(fileName)
{
}

void Tester::slotParallelIterationDone()
{
    static uint countPassedCycles = 0;
    countPassedCycles++;

    if (countPassedCycles == cycles) {
        countPassedCycles = 0;
        disconnect(myServer, SIGNAL(endMultiply(QVector<QVector<qint64> >&)), this, SLOT(slotParallelIterationDone()));
        QTime t3 = QTime::currentTime();

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            cerr << "File cannot be open for results of tests" << endl;
            emit errorOpenFile();
            return;
        }

        QTextStream stream(&file);


        uint parallelTimeMsec = t2.msecsTo(t3);

        uint seriesTimeMsec = t1.msecsTo(t2);

        stream << QTime::currentTime().toString() << ": cycles: " << cycles << " A[N1*N2]*B[N2*N3] N1 = " << N1 << " N2 = " << N2 << " N3 = " << N3 << endl;
        stream << "series time(msec): " << seriesTimeMsec << " parallel time(msec): " << parallelTimeMsec << " computers: " << myServer->getClients()->count() << endl << endl;

        emit successfulDone();
    }
    else {
        parallel_multiply();
    }
}

QVector<QVector<qint64> > Tester::init_matrix(uint n, uint m)
{
    QVector<qint64> row;
    QVector<QVector<qint64> > res;
    for(uint i = 0; i < n; i++) {
        row.clear();
        for(uint j = 0; j < m; j++) {
            row << rand() % 1000; // в интервале от 0 до 999
        }
        res << row;
    }
    return res;
}

// последовательное умножение матриц
void Tester::series_multiply()
{
    QVector<QVector<qint64> > a = init_matrix(N1, N2);
    QVector<QVector<qint64> > b = init_matrix(N2, N3);

    QVector<QVector<qint64> > res;

    //    N1 - высота a
    //    N2 - ширина a, высота b
    //    N3 - ширина b
    qint64 N1 = a.count();
    qint64 N2 = 0;
    if (!a.isEmpty()) {
        N2 = a[0].count();
    }
    qint64 N3 = 0;
    if (!b.isEmpty()) {
        N3 = b[0].count();
    }

    QVector<qint64> row;

    for (qint64 i = 0; i < N1; i++) {
        row.clear();
        for (qint64 j = 0; j < N3; j++) {
            qint64 summa = 0;
            for (qint64 k = 0; k < N2; k++) {
                summa += a[i][k] * b[k][j];
            }
            row << summa;
        }
        res << row;
    }

}

void Tester::print_matrix(QVector<QVector<qint64> > a)
{
    for (qint64 i = 0; i < a.count(); i++) {
        for (qint64 j = 0; j < a[0].count(); j++) {
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }
}

void Tester::parallel_multiply()
{
    QVector<QVector<qint64> > a = init_matrix(N1, N2);
    QVector<QVector<qint64> > b = init_matrix(N2, N3);

    MultiplyInit init;
    init.a = a;
    init.b = b;
    myServer->getInit(init);

    myServer->startMultiply();
}

void Tester::test()
{
    srand(time(0));

    t1 = QTime::currentTime();

    for (uint i = 0; i < cycles; i++) {
        series_multiply();
    }

    t2 = QTime::currentTime();



    connect(myServer, SIGNAL(endMultiply(QVector<QVector<qint64> >&)), this, SLOT(slotParallelIterationDone()));

    parallel_multiply();

}
