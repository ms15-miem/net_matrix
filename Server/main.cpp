#include <QApplication>
#include "mainwindow.h"
#include "tester.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    /*   MyServer     server(2323);
       Tester *tester = new Tester(1, 200, 200, 200, &server, "tests.txt");
       connect(tester, SIGNAL(successfulDone()), tester, SLOT(deleteLater()));
       connect(tester, SIGNAL(errorOpenFile()), tester, SLOT(deleteLater()));
       tester->test(); */
    MainWindow m;
    m.show();
    return app.exec();
}
