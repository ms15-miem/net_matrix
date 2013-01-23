#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QVector>
#include "MyServer.h"
//Главное окно
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    MyServer *server;
    QStatusBar *bar;
    QPushButton *multiplyButton;
    QLabel *clientsLabel;

    QRadioButton* firstFromFile;
    QRadioButton* firstFromWidget;

    QLineEdit *firstPathEdit;
    QPushButton *loadFirstFileButton;
    QLineEdit *firstXEdit;
    QLineEdit *firstYEdit;
    QTableView* firstTable;
    QStandardItemModel *firstModel;

    QRadioButton* secondFromFile;
    QRadioButton* secondFromWidget;

    QLineEdit *secondPathEdit;
    QPushButton *loadSecondFileButton;
    QLineEdit *secondXEdit;
    QLineEdit *secondYEdit;
    QTableView *secondTable;
    QStandardItemModel *secondModel;

    QLineEdit *outputEdit;
    QPushButton *outputPathButton;
    QPushButton *testButton;
    QLineEdit *testEdit;

    QLayout *createFirstDimensionLayout();
    QLayout *createSecondDimensionLayout();
    QLayout *createFirstLoadLayout();
    QLayout *createSecondLoadLayout();
    QLayout *createOutputLayout();
    QGroupBox *createFirstBox();
    QGroupBox *createSecondBox();

    QVector< QVector<qint64 > > getMatrixFromFile(QString path, bool *ok);
    QVector< QVector<qint64 > > getMatrixFromWidget(QStandardItemModel *model, bool *ok);
    void saveMatrixToFile(QVector<QVector<qint64 > > FromObj,QString ToFilePath, bool* ok = 0);
public:
    explicit MainWindow(QWidget *parent = 0);

signals:
    void runTest();

public slots:
    void firstFromFileImpl(bool b);
    void firstFromWidgetImpl(bool b);
    void secondFromFileImpl(bool b);
    void secondFromWidgetImpl(bool b);
    void firstLoadImpl();
    void secondLoadImpl();
    void firstXImpl(QString str);
    void firstYImpl(QString str);
    void secondXImpl(QString str);
    void secondYImpl(QString str);
    void multiplyImpl();
    void resultImpl(QVector<QVector<qint64 > > &mat);
    void clientsCountChange(qint64 count);
    void doneImpl(qreal done);
    void outputBrowseImpl();
    void testRun();
    void testFinishImpl();

};

#endif // MAINWINDOW_H
