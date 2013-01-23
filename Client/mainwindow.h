#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "MyClient.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QStatusBar *bar;
    QPushButton *button;
    QLineEdit *ipEdit;
    QLineEdit *portEdit;
    MyClient *client;

    void createWidgets();
    void createClient(const QString& strHost, qint64 nPort);

public:
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:
  void slotButtonClicked();
  void slotConnectionError(QString err);
  void slotConnectionEstablished();
};

#endif // MAINWINDOW_H
