#include <QTcpSocket>
#include "MyClient.h"
#include "../commands.h"
#include "../servclient.h"

MyClient::MyClient(const QString& str,
                   qint64            port,
                   QObject*       pwgt /*=0*/
                   ) : ServClient(pwgt), nPort(port), strHost(str)
{
    m_pTcpSocket = new QTcpSocket(this);
    // подключеные сетевых сигналов

        connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
        connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
        connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                this,         SLOT(slotError(QAbstractSocket::SocketError))
                );
                m_pTcpSocket->connectToHost(strHost, nPort);

}

void MyClient::readedCom(QTcpSocket* socket,QDataStream &in, command com)
{
    if (com == MULTIPLY_REQUEST) {
        MultiplyRequst req;
        in >> req;

        qint64 res = 0;

        for (qint64 k = 0; k < a.count(); k++) {
            res += a[req.i][k]*b[k][req.j];
        }

        MultiplyRespone resp;
        resp.i = req.i;
        resp.j =req.j;
        resp.result = res;
        if(resp.i>1000||resp.j>1000)
            qDebug()<<"HALT";
        sendToClient(socket, resp, MULTIPLY_REQUEST);
    }
    else if (com == MULTIPLY_INIT) {
        MultiplyInit init;
        //qDebug()<<in.
        in >> init;
        a = init.a;
        b = init.b;
    }
}

// ----------------------------------------------------------------------
void MyClient::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
            "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                             "The host was not found." :
                             err == QAbstractSocket::RemoteHostClosedError ?
                                 "The remote host is closed." :
                                 err == QAbstractSocket::ConnectionRefusedError ?
                                     "The connection was refused." :
                                     QString(m_pTcpSocket->errorString())
                                     );
//    QTextStream(stdout) << strError << endl;
    emit connectionError(strError);
}

// ----------------------------------------------------------------------
void MyClient::slotSendToServer()
{

}

// ------------------------------------------------------------------
void MyClient::slotConnected()
{

}

