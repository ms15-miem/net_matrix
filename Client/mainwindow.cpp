#include "mainwindow.h"
#include "MyClient.h"

//Комментарий
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    client = 0;

    createWidgets();

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(ipEdit);
    layout->addWidget(portEdit);
    layout->addWidget(button);

    QWidget *central = new QWidget();
    central->setLayout(layout);
    central->adjustSize();

    this->setCentralWidget(central);
    this->adjustSize();
    this->setFixedSize(this->sizeHint());
}

void MainWindow::createWidgets()
{

    bar = this->statusBar();
    bar->setSizeGripEnabled(false);

    ipEdit = new QLineEdit("127.0.0.1");
    ipEdit->setMinimumWidth(100);

    portEdit = new QLineEdit("2323");
    portEdit->setFixedWidth(50);

    button = new QPushButton("Connect");
    connect(button, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));

}

void MainWindow::slotButtonClicked()
{
    bool ok;
    qint64 port = portEdit->text().toInt(&ok);
    if (ok)
    {
        createClient(ipEdit->text(), port);
        this->centralWidget()->setEnabled(false);
    }
    else
        bar->showMessage("Invalid port");
}

void MainWindow::slotConnectionError(QString err)
{
    bar->showMessage(err);
    this->centralWidget()->setEnabled(true);
    client->deleteLater();
}

void MainWindow::slotConnectionEstablished()
{
    bar->showMessage("Connection Established");
}

void MainWindow::createClient(const QString& strHost, qint64 nPort)
{
    client = new MyClient(strHost, nPort, this);
    connect(client, SIGNAL(connectionError(QString)), this, SLOT(slotConnectionError(QString)));
    connect(client, SIGNAL(signalReadyRead()), this, SLOT(slotConnectionEstablished()));

}
