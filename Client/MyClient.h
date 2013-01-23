#ifndef _MyClient_h_
#define _MyClient_h_

#include <../commands.h>
#include <QTcpSocket>
#include "../servclient.h"


class QTextEdit;
class QLineEdit;

// ======================================================================
class MyClient : public ServClient {
    Q_OBJECT
protected:
    qint64 nPort;
    const QString strHost;
    QTcpSocket* m_pTcpSocket;

    QVector<QVector<qint64 > > a;
    QVector<QVector<qint64 > > b;

    void readedCom(QTcpSocket* socket, QDataStream &in, command com);

public:
    MyClient(const QString& strHost, qint64 nPort, QObject* pwgt = 0) ;
protected slots:
    void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer(                            );
    void slotConnected   (                            );
signals:
    void connectionError(QString Error);
};
#endif  //_MyClient_h_
