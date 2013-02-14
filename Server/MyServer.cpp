#include "MyServer.h"
#include <QTcpServer>
#include <QTcpSocket>

MyServer::MyServer(qint64 nPort, QObject* pwgt /*=0*/) : ServClient(pwgt),
    countTotalRequests(0), countResponses(0), idle(true)
{

    QTextStream qerr(stderr);
    m_ptcpServer = new QTcpServer(this);
    if (!m_ptcpServer->listen(QHostAddress::Any, nPort)) {
        qerr << m_ptcpServer->errorString() << endl;
        m_ptcpServer->close();
        return;
    }
    connect(m_ptcpServer, SIGNAL(newConnection()),
            this,         SLOT(slotNewConnection())
            );
}


void MyServer::getInit(MultiplyInit &Init)
{
    qint64 i;
    init.a.clear();
    qint64 rows = Init.a.size();
    for (i = 0; i < rows; i++)
    {
        init.a << Init.a[i];
    }

    init.b.clear();
    rows = Init.b.size();
    for (i = 0; i < rows; i++)
    {
        init.b << Init.b[i];
    }

    rows = init.a.size();
    qint64 cols = init.b[0].size();
    multiplyResult.resize(rows);
    for (i = 0; i < rows; i++)
        multiplyResult[i].resize(cols);
}

// ----------------------------------------------------------------------
/*virtual*/ void MyServer::slotNewConnection()
{
    idle = false;

    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();
    MultiplyRequst req;


    clients << pClientSocket;
    clientRequests<<req;
    emit clientsCountChange(clients.size());

    connect(pClientSocket, SIGNAL(readyRead()),
            this,          SLOT(slotReadyRead())
            );

    connect(pClientSocket, SIGNAL(disconnected()),
            this, SLOT(userDisconnected())
            );

    connect(pClientSocket, SIGNAL(disconnected()),
            pClientSocket, SLOT(deleteLater())
            );
}


void MyServer::readedCom(QTcpSocket* pClientSocket,QDataStream &in, command com)
{
    if (com == MULTIPLY_REQUEST) {
        MultiplyRespone resp;
        in >> resp;
        for(qint64 i=0; i<resp.count(); i++)
        {
            multiplyResult[resp[i].i][resp[i].j] = resp[i].result;
        }

        countResponses++;
        emit done(qreal(countResponses)/countTotalRequests * 100);

        if (countTotalRequests == countResponses) {
            emit endMultiply(multiplyResult);
            countResponses = 0;
        }
    }
}

MyServer::~MyServer()
{

}

const QVector<QTcpSocket *> *MyServer::getClients() const
{
    return &clients;
}

void MyServer::userDisconnected()
{
    QTcpSocket *socket = (QTcpSocket*) sender();
    for (qint64 i = 0; i < clients.count(); ++i) {
        if (clients[i] == socket) {
            clients.remove(i);
            break;
        }
    }
    countResponses--;
    emit clientsCountChange(clients.size());
}


void MyServer::startMultiply()
{
    if (clients.empty())
        return;

    emit done(0);
    idle = false;
    //sending init
    qint64 clientsCount = clients.count();
    for (qint64 i = 0; i < clientsCount; i++)
        sendToClient(clients[i], init, MULTIPLY_INIT);

    //sending requests, w|o counting disconnected
    qint64 rows = init.a.size(), cols = init.b[0].size();
    countTotalRequests = clients.count();

    nextReceiver = 0;

    for (qint64 ai = 0; ai < rows; ai++)
      for (qint64 bj = 0; bj < cols; bj++)
      {
          if (!clients.isEmpty())
          {
              clientRequests[nextReceiver].add(ai,bj);
              nextReceiver = (nextReceiver+1) % clientsCount;
          }
      }
    for(qint64 i = 0; i<clientsCount; i++)
    {
        sendToClient(clients[i], clientRequests[i],MULTIPLY_REQUEST);
        clientRequests[i].clear();
    }

}
