#ifndef _MyServer_h_
#define _MyServer_h_
#include "../servclient.h"
#include <QQueue>

class QTcpServer;


class MyServer : public ServClient {
    Q_OBJECT

protected:
    QTcpServer* m_ptcpServer;
    void readedCom(QTcpSocket* pClientSocket,QDataStream &in, command com);

    qint64 countTotalRequests;
    qint64 countResponses;

    QVector<QTcpSocket *> clients;
    QVector<MultiplyRequst> clientRequests;
    qint64 nextReceiver;
    bool idle;

    MultiplyInit init;
    QVector<QVector<qint64> > multiplyResult;


public:
    MyServer(qint64 nPort, QObject* pwgt = 0);
    ~MyServer();

    const QVector<QTcpSocket *>* getClients() const;

protected slots:
    virtual void slotNewConnection();
    void userDisconnected();

public slots:
    /*Q_INVOKABLE */void startMultiply();
    /*Q_INVOKABLE */void getInit(MultiplyInit Init);


signals:
    void endMultiply(QVector<QVector<qint64> > res);
    void clientsCountChange(qint64 count);
    void done(qreal percent);
};
#endif  //_MyServer_h_
