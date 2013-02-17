#ifndef TESTER_H
#define TESTER_H

#include <QObject>

#include <QTime>
#include <QVector>
#include <cstdlib>
#include <iostream>
#include <QFile>
#include "MyServer.h"
#include <ctime>

using namespace std;

class Tester : public QObject
{
    Q_OBJECT

// N1 - высота первой матрицы
// N2 - ширина первой матрицы, высота второй матрицы
// N3 - ширина второй матрицы
    uint N1, N2, N3;

    uint cycles;

    MyServer *myServer;
    QString fileName;

    // начало теста
    QTime t1;
    // время после последовательного умножения
    QTime t2;
    // время после параллельного умножения
    QTime t3;

    // последовательное умножение матриц
    void series_multiply();

    void parallel_multiply();

public:

       static void print_matrix(QVector<QVector<qint64> > a);

       /**
        * @brief init - инициализация матрицы
        * @param n - число строк
        * @param m - число столбцов
        * @return матрица
        */
       static QVector<QVector<qint64> > init_matrix(uint n, uint m);

public:
    explicit Tester(uint cycles, uint N1, uint N2, uint N3, MyServer *myServer, QString fileName, QObject *parent = 0);
    
signals:
    void successfulDone();
    void errorOpenFile();

public slots:
    /**
     * @brief test - сравнение последовательного и параллельного алгоритмов на рандомных матрицах
     * @param N1 - высота первой матрицы
     * @param N2 - ширина первой матрицы, высота второй матрицы
     * @param N3 - ширина второй матрицы
     * @param cycles - число однотипных тестов
     */
    void test();

public slots:
    void slotParallelIterationDone(QVector<QVector<qint64> >);
};

#endif // TESTER_H
