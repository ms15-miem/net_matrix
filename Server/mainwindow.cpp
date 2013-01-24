#include <QDebug>
#include "mainwindow.h"
#include "tester.h"

//Конструктор
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    server = new MyServer(2323,this);
    connect(server, SIGNAL(endMultiply(QVector<QVector<qint64> >&)), this, SLOT(resultImpl(QVector<QVector<qint64> >&));
    connect(server, SIGNAL(clientsCountChange(qint64)), this, SLOT(clientsCountChange(qint64)));
    connect(server, SIGNAL(done(qreal)), this, SLOT(doneImpl(qreal)));

    bar = this->statusBar();
    clientsLabel = new QLabel("Clients: 0");
    bar->addPermanentWidget(clientsLabel);

    //Для первой матрицы
    QGroupBox* firstGroupBox = createFirstBox();

    //Для второй матрицы
    QGroupBox* secondGroupBox = createSecondBox();

    QHBoxLayout *boxesLayout = new QHBoxLayout();
    boxesLayout->addWidget(firstGroupBox);
    boxesLayout->addWidget(secondGroupBox);


    QVBoxLayout *layout = new QVBoxLayout();
    QLayout* outputLayout = createOutputLayout();
    QGroupBox* outputBox = new QGroupBox("Output");
    outputBox->setLayout(outputLayout);
    layout->addLayout(boxesLayout);
    layout->addWidget(outputBox);

    QWidget* central = new QWidget();
    central->setLayout(layout);
    this->setCentralWidget(central);

}

void MainWindow::firstFromFileImpl(bool b)
{
    if(b)
    {
        firstPathEdit->setEnabled(true);
        loadFirstFileButton->setEnabled(true);
        firstXEdit->setEnabled(false);
        firstYEdit->setEnabled(false);
        firstTable->setEnabled(false);
    }
}

void MainWindow::firstFromWidgetImpl(bool b)
{
    if(b)
    {
        firstPathEdit->setEnabled(false);
        loadFirstFileButton->setEnabled(false);
        firstXEdit->setEnabled(true);
        firstYEdit->setEnabled(true);
        firstTable->setEnabled(true);
    }
}

void MainWindow::secondFromFileImpl(bool b)
{
    if(b)
    {
        secondPathEdit->setEnabled(true);
        loadSecondFileButton->setEnabled(true);
        secondXEdit->setEnabled(false);
        secondYEdit->setEnabled(false);
        secondTable->setEnabled(false);
    }
}

void MainWindow::secondFromWidgetImpl(bool b)
{
    if(b)
    {
        secondPathEdit->setEnabled(false);
        loadSecondFileButton->setEnabled(false);
        secondXEdit->setEnabled(true);
        secondYEdit->setEnabled(true);
        secondTable->setEnabled(true);
    }
}

void MainWindow::firstLoadImpl()
{
    QString s = QFileDialog::getOpenFileName();
    firstPathEdit->setText(s);
}

void MainWindow::firstXImpl(QString str)
{
    bool ok;
    qint64 num = str.toInt(&ok);
    if(ok && num>0 && num < 10)
    {
        qint64 prevNum = firstModel->rowCount();
        for(qint64 i=prevNum-1; i>=num; i--)
        {
            firstModel->removeRow(i);
        }

        for(qint64 i = prevNum; i<num;i++)
        {
            QList<QStandardItem* > items;
            for(qint64 j = 0; j<firstModel->columnCount(); j++)
            {
                items.append(new QStandardItem("0"));
            }
            firstModel->appendRow(items);
        }
    }
}

void MainWindow::firstYImpl(QString str)
{
    bool ok;
    qint64 num = str.toInt(&ok);
    if(ok && num>0 && num < 10)
    {
        qint64 prevNum = firstModel->columnCount();
        for(qint64 i=prevNum-1; i>=num; i--)
        {
            firstModel->removeColumn(i);
        }

        for(qint64 i = prevNum; i<num;i++)
        {
            QList<QStandardItem* > items;
            for(qint64 j = 0; j<firstModel->rowCount(); j++)
            {
                items.append(new QStandardItem("0"));
            }
            firstModel->appendColumn(items);
        }
    }

}

void MainWindow::secondLoadImpl()
{
    QString s = QFileDialog::getOpenFileName();
    secondPathEdit->setText(s);
}

void MainWindow::secondXImpl(QString str)
{
    bool ok;
    qint64 num = str.toInt(&ok);
    if(ok && num>0 && num < 10)
    {
        qint64 prevNum = secondModel->rowCount();
        for(qint64 i=prevNum-1; i>=num; i--)
        {
            secondModel->removeRow(i);
        }

        for(qint64 i = prevNum; i<num;i++)
        {
            QList<QStandardItem* > items;
            for(qint64 j = 0; j<secondModel->columnCount(); j++)
            {
                items.append(new QStandardItem("0"));
            }
            secondModel->appendRow(items);
        }
    }
}

void MainWindow::secondYImpl(QString str)
{
    bool ok;
    qint64 num = str.toInt(&ok);
    if(ok && num>0 && num < 10)
    {
        qint64 prevNum = secondModel->columnCount();
        for(qint64 i=prevNum-1; i>=num; i--)
        {
            secondModel->removeColumn(i);
        }

        for(qint64 i = prevNum; i<num;i++)
        {
            QList<QStandardItem* > items;
            for(qint64 j = 0; j<secondModel->rowCount(); j++)
            {
                items.append(new QStandardItem("0"));
            }
            secondModel->appendColumn(items);
        }
    }

}

QLayout *MainWindow::createFirstDimensionLayout()
{

    QLabel *firstXLabel = new QLabel("Rows:");
    QLabel *firstYLabel = new QLabel("Columns:");

    firstXEdit = new QLineEdit("3");
    firstXEdit->setFixedWidth(20);
    firstXEdit->setEnabled(false);
    connect(firstXEdit, SIGNAL(textChanged(QString)),this, SLOT(firstXImpl(QString)));

    firstYEdit = new QLineEdit("3");
    firstYEdit->setFixedWidth(20);
    firstYEdit->setEnabled(false);
    connect(firstYEdit, SIGNAL(textChanged(QString)), this, SLOT(firstYImpl(QString)));

    QHBoxLayout *firstDimensionsLayout = new QHBoxLayout();
    firstDimensionsLayout->addWidget(firstXLabel);
    firstDimensionsLayout->addWidget(firstXEdit);
    firstDimensionsLayout->addStretch(1);
    firstDimensionsLayout->addWidget(firstYLabel);
    firstDimensionsLayout->addWidget(firstYEdit);

    return firstDimensionsLayout;
}

QLayout *MainWindow::createSecondDimensionLayout()
{
    QLabel *secondXLabel = new QLabel("Rows:");
    QLabel *secondYLabel = new QLabel("Columns:");

    secondXEdit = new QLineEdit("3");
    secondXEdit->setFixedWidth(20);
    secondXEdit->setEnabled(false);
    connect(secondXEdit, SIGNAL(textChanged(QString)), this, SLOT(secondXImpl(QString)));

    secondYEdit = new QLineEdit("3");
    secondYEdit->setFixedWidth(20);
    secondYEdit->setEnabled(false);
    connect(secondYEdit, SIGNAL(textChanged(QString)), this, SLOT(secondYImpl(QString)));

    QHBoxLayout *secondDimensionsLayout = new QHBoxLayout();
    secondDimensionsLayout->addWidget(secondXLabel);
    secondDimensionsLayout->addWidget(secondXEdit);
    secondDimensionsLayout->addStretch(1);
    secondDimensionsLayout->addWidget(secondYLabel);
    secondDimensionsLayout->addWidget(secondYEdit);

    return secondDimensionsLayout;
}

QLayout *MainWindow::createFirstLoadLayout()
{
    firstPathEdit = new QLineEdit();
    firstPathEdit->setEnabled(true);

    loadFirstFileButton = new QPushButton("...");
    loadFirstFileButton->setEnabled(true);
    connect(loadFirstFileButton,SIGNAL(clicked()), this, SLOT(firstLoadImpl()));

    QHBoxLayout *firstLoadLayout = new QHBoxLayout();
    firstLoadLayout->addWidget(firstPathEdit);
    firstLoadLayout->addWidget(loadFirstFileButton);

    return firstLoadLayout;
}

QLayout *MainWindow::createSecondLoadLayout()
{
    secondPathEdit = new QLineEdit();
    secondPathEdit->setEnabled(true);

    loadSecondFileButton = new QPushButton("...");
    loadSecondFileButton->setEnabled(true);
    connect(loadSecondFileButton, SIGNAL(clicked()), this, SLOT(secondLoadImpl()));

    QHBoxLayout *secondLoadLayout = new QHBoxLayout();
    secondLoadLayout->addWidget(secondPathEdit);
    secondLoadLayout->addWidget(loadSecondFileButton);

    return secondLoadLayout;
}

QGroupBox* MainWindow::createFirstBox()
{


    QLayout* firstDimensionsLayout = createFirstDimensionLayout();
    QLayout* firstLoadLayout = createFirstLoadLayout();

    firstFromFile = new QRadioButton("Load from file");
    connect(firstFromFile, SIGNAL(clicked(bool)), this, SLOT(firstFromFileImpl(bool)));
    firstFromFile->setChecked(true);

    firstFromWidget = new QRadioButton("Input manually");
    connect(firstFromWidget, SIGNAL(clicked(bool)), this, SLOT(firstFromWidgetImpl(bool)));    QGroupBox* firstGroupBox= new QGroupBox("First Matrix");

    firstTable = new QTableView();
    firstTable->setEnabled(false);
    firstModel = new QStandardItemModel(3,3);
    firstTable->setModel(firstModel);
    for(qint64 i=0; i<firstModel->rowCount(); i++)
    {
        for(qint64 j=0; j<firstModel->columnCount();j++)
        {
            if (i==j)
            {
                QStandardItem *item = new QStandardItem("1");
                firstModel->setItem(i,j, item);
            }
            else
            {
                QStandardItem *item = new QStandardItem("0");
                firstModel->setItem(i,j, item);
            }

        }
    }

    QVBoxLayout *firstBoxLayout = new QVBoxLayout();

    firstBoxLayout->addWidget(firstFromFile);
    firstBoxLayout->addLayout(firstLoadLayout);
    firstBoxLayout->addWidget(firstFromWidget);
    firstBoxLayout->addLayout(firstDimensionsLayout);
    firstBoxLayout->addWidget(firstTable);

    firstGroupBox->setLayout(firstBoxLayout);

    return firstGroupBox;

}

void MainWindow::multiplyImpl()
{
    MultiplyInit m;
    bool ok = true;
    if(firstFromFile->isChecked())
    {
        m.a =  getMatrixFromFile(firstPathEdit->text(),&ok);
    }
    else
    {
        m.a = getMatrixFromWidget(firstModel, &ok);
    }
    if (m.a.count() == 0)
    {
        ok = false;
    }
    else if (m.a[0].count() == 0)
    {
        ok = false;
    }

    if(!ok)
    {
        bar->showMessage("Invalid first matrix.");
        return;
    }

    if(secondFromFile->isChecked())
    {
        m.b = getMatrixFromFile(secondPathEdit->text(), &ok);
    }
    else
    {
        m.b = getMatrixFromWidget(secondModel, &ok);
    }

    if (m.b.count() == 0)
    {
        ok = false;
    }
    else if (m.b[0].count() == 0)
    {
        ok = false;
    }

    if(!ok)
    {
        bar->showMessage("Invalid second matrix.");
        return;
    }

    if(m.a[0].count() != m.b.count())
    {
        bar->showMessage("Matrix dimensions must agree.");
        return;
    }

    if(ok)
    {
        server->getInit(m);
        server->startMultiply();
    }


}

void MainWindow::saveMatrixToFile(QVector<QVector<qint64 > > FromObj,QString ToFilePath, bool* ok)
{
   QFile file(ToFilePath);
   if (!file.open(QIODevice::WriteOnly| QIODevice::Text))
   {
       *ok = false;
       return;
   }
   if (FromObj.count()==0)
   {
       *ok = false;
       return;
   }

   for(qint64 i = 0; i < FromObj.count(); i++)
   {
       for(qint64 j = 0; j < FromObj.count(); j++)
       {
           QTextStream out(&file);
           //out.setEncoding(QTextStream::UnicodeUTF8);
           out<<FromObj[i][j];
           if (j!=FromObj[i].count()-1)
               out<<',';
           else out<<'\n';
       }
   }
   *ok = true;
   return;
}

void MainWindow::resultImpl(QVector<QVector<qint64 > > &mat)
{
    bool ok = true;
    saveMatrixToFile(mat, outputEdit->text(), &ok);
    if (!ok)
        bar->showMessage("Writing error.");
}

void MainWindow::clientsCountChange(qint64 count)
{
    QString str;
    clientsLabel->setText("Clients: " + str.setNum(count));
}

void MainWindow::doneImpl(qreal done)
{
    QString str;
    str.setNum(done,'f',2);
    bar->showMessage("Done: " + str + "%");
}

QVector< QVector<qint64 > > MainWindow::getMatrixFromFile(QString FilePath, bool* ok = 0)
{
    /*  Matlab
       Export: dlmwrite('matrix.txt', somematrix)
       Import: dlmread('matrix.txt'')
       matrix.txt format:
       new row - new line
       comma separated cells in row
       Example: Matrix 3x5.
       1,2,3,4,5
       5,4,3,2,1
       0,0,0,0,0
       */
       QFile file(FilePath);
       QVector<QVector<qint64 > > result;
       QVector<qint64 > row;
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
       {
           *ok = false;
           return result;
       }
       for (qint64 i=0;!file.atEnd();i++)
       {
               QByteArray line = file.readLine(); //row
               QString current_row = line.data();
               QStringList List;//cells
               List=current_row.split(',');
               for (qint64 j=0;j<List.size();j++)
               {
                   row<<List[j].toInt();
               }
               result<<row;
               row.clear();
       }
       *ok = true;
       return result;
}

QVector<QVector<qint64 > > MainWindow::getMatrixFromWidget(QStandardItemModel* model, bool* _ok = 0)
{
    bool ok = true;
    QVector<QVector<qint64 > > mat;
    for(qint64 i =0; i<model->rowCount(); i++)
    {
        QVector<qint64 > row;
        for(qint64 j=0; j<model->columnCount(); j++)
        {
            qint64 num = model->item(i, j)->text().toInt(&ok);
            if(!ok)
            {
                break;
            }
            row<< num;
        }
        if(!ok)
        {
            break;
        }
        mat<<row;
    }
    *_ok = ok;
    return mat;
}

QGroupBox* MainWindow::createSecondBox()
{

    QGroupBox* secondGroupBox= new QGroupBox("Second Matrix");

    QLayout *secondDimensionsLayout = createSecondDimensionLayout();
    QLayout *secondLoadLayout = createSecondLoadLayout();

    secondFromFile = new QRadioButton("Load from file");
    secondFromFile->setChecked(true);
    connect(secondFromFile, SIGNAL(clicked(bool)), this, SLOT(secondFromFileImpl(bool)));

    secondFromWidget = new QRadioButton("Input manually");
    connect(secondFromWidget, SIGNAL(clicked(bool)), this, SLOT(secondFromWidgetImpl(bool)));

    secondTable = new QTableView();
    secondTable->setEnabled(false);
    secondModel = new QStandardItemModel(3,3);
    secondTable->setModel(secondModel);
    for(qint64 i=0; i<secondModel->rowCount(); i++)
    {
        for(qint64 j=0; j<secondModel->columnCount();j++)
        {
            if (i==j)
            {
                QStandardItem *item = new QStandardItem("1");
                secondModel->setItem(i,j, item);
            }
            else
            {
                QStandardItem *item = new QStandardItem("0");
                secondModel->setItem(i,j, item);
            }

        }
    }


    QVBoxLayout *secondBoxLayout = new QVBoxLayout();

    secondBoxLayout->addWidget(secondFromFile);
    secondBoxLayout->addLayout(secondLoadLayout);
    secondBoxLayout->addWidget(secondFromWidget);
    secondBoxLayout->addLayout(secondDimensionsLayout);
    secondBoxLayout->addWidget(secondTable);

    secondGroupBox->setLayout(secondBoxLayout);

    return secondGroupBox;
}

QLayout * MainWindow::createOutputLayout()
{
    QHBoxLayout *outputLayout = new QHBoxLayout();

    multiplyButton = new QPushButton("Multiply");
    connect(multiplyButton, SIGNAL(clicked()), this, SLOT(multiplyImpl()));

    outputEdit = new QLineEdit();

    outputPathButton = new QPushButton("...");
    connect(outputPathButton, SIGNAL(clicked()), this, SLOT(outputBrowseImpl()));


    testButton = new QPushButton("Test");
    connect(testButton, SIGNAL(clicked()), this, SLOT(testRun()));

    testEdit = new QLineEdit();
    testEdit->setFixedWidth(100);

    outputLayout->addWidget(outputEdit);
    outputLayout->addWidget(outputPathButton);
    outputLayout->addStretch(1);
    outputLayout->addWidget(multiplyButton);
    outputLayout->addWidget(testButton);
    outputLayout->addWidget(testEdit);

    return outputLayout;
}

void MainWindow::outputBrowseImpl()
{
    QString s = QFileDialog::getSaveFileName();
    outputEdit->setText(s);
}


void MainWindow::testRun()
{
    testButton->setEnabled(false);
    bool ok = true;
    qint64 num = testEdit->text().toInt(&ok);
    if(!ok)
        num = 200;
    Tester *tester = new Tester(1, num, num, num, server, "tests.txt");
    connect(tester, SIGNAL(successfulDone()), tester, SLOT(deleteLater()));
    connect(tester, SIGNAL(errorOpenFile()), tester, SLOT(deleteLater()));
    connect(tester, SIGNAL(successfulDone()), this, SLOT(testFinishImpl()));
    connect(tester, SIGNAL(errorOpenFile()), this, SLOT(testFinishImpl()));

    tester->test();
}

void MainWindow::testFinishImpl()
{
    testButton->setEnabled(true);
}

