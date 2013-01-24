#ifndef SERVCLIENT_H
#define SERVCLIENT_H

#include "commands.h"
#include <QTcpSocket>

// пустой класс, который может быть отправлен в поток
class EmptyClass {};

QDataStream & operator<< (QDataStream& stream, const EmptyClass& p);
QDataStream & operator>> (QDataStream& stream, EmptyClass& p);

struct MultiplyRequst: QVector<QPair<qint64,qint64> >
{
   void add(qint64 _i=0, qint64 _j=0);
};

//QDataStream & operator<< (QDataStream& stream, const MultiplyRequst& p);
//QDataStream & operator>> (QDataStream& stream, MultiplyRequst& p);

struct MultiplyInit
{
    QVector<QVector<qint64> > a;
    QVector<QVector<qint64> > b;
};

QDataStream & operator<< (QDataStream& stream, const MultiplyInit& p);
QDataStream & operator>> (QDataStream& stream, MultiplyInit& p);

struct MultiplyResult
{
    qint64 i;
    qint64 j;
    qint64 result;
};


struct MultiplyRespone: QVector<MultiplyResult>
{
    void add(qint64 i, qint64 j, qint64 result);
};


QDataStream & operator<< (QDataStream& stream, const MultiplyResult& p);
QDataStream & operator>> (QDataStream& stream, MultiplyResult& p);

// общий класс для клиента и сервера
class ServClient:public QObject
{
    Q_OBJECT
private:
            qint64     m_nNextBlockSize;
public:
    ServClient(QObject* o = 0);
protected:
    template <class Type>
    void sendToClient (QTcpSocket* pSocket, const Type& typeElement, command com)
    {
        QByteArray  arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_2);
        out << qint64(0) << (quint8)com;
        out << typeElement;
        out.device()->seek(0);
        out << qint64(arrBlock.size() - sizeof(qint64));

        pSocket->write(arrBlock);
    }

    // реагируем на команду com
    virtual void readedCom(QTcpSocket* pClientSocket,QDataStream &in, command com)=0;

protected slots:
    void slotReadyRead();
signals:
    void signalReadyRead();

};

#endif // SERVCLIENT_H
