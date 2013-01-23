#include <QApplication>
#include <QtGui>
#include "MyClient.h"
#include "mainwindow.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainWindow m;
    m.show();

    return app.exec();
}
