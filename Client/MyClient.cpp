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
        MultiplyRespone resp;
        qint64 num = req.count();
        for(qint64 i = 0; i<num; i++)
        {
            qint64 res = 0;

            for (qint64 k = 0; k < b.count(); k++) {
                res += a[req[i].first][k]*b[k][req[i].second];
            }

            resp.add(req[i].first, req[i].second, res);
        }
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

