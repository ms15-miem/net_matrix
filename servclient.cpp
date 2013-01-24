#include "servclient.h"

QDataStream & operator<< (QDataStream& stream, const EmptyClass&){return stream;}
QDataStream & operator>> (QDataStream& stream, EmptyClass&){return stream;}
/*
QDataStream & operator<< (QDataStream& stream, const MultiplyRequst& p)
{
    return stream << p.i << p.j;
}

QDataStream & operator>> (QDataStream& stream, MultiplyRequst& p)
{
    return stream >> p.i >> p.j;
}
*/
QDataStream & operator<< (QDataStream& stream, const MultiplyResult& p)
{
    return stream << p.i << p.j << p.result;
}

QDataStream & operator>> (QDataStream& stream, MultiplyResult& p)
{
    return stream >> p.i >> p.j >> p.result;
}


QDataStream & operator<< (QDataStream& stream, const MultiplyInit& p)
{
    return stream << p.a << p.b;
}

QDataStream & operator>> (QDataStream& stream, MultiplyInit& p)
{
    return stream >> p.a >> p.b;
}

void ServClient::slotReadyRead()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_4_2);
    emit signalReadyRead();
    for (;;) {
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < (qint64)sizeof(qint64)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }

        quint8 c;
        in >> c;
        command com = (command) c;

        readedCom(pClientSocket,in,com);

        m_nNextBlockSize = 0;
    }
}

ServClient::ServClient(QObject *o):QObject(o),m_nNextBlockSize(0) {}
/*
MultiplyRequst::MultiplyRequst(qint64 _i, qint64 _j)
{
    i = _i;
    j = _j;
}
*/

void MultiplyRequst::add(qint64 _i, qint64 _j)
{
    QPair<qint64,qint64> p(_i,_j);
    this->append(p);
}




void MultiplyRespone::add(qint64 i, qint64 j, qint64 result)
{
    MultiplyResult r;
    r.i = i;
    r.j = j;
    r.result = result;
    this->append(r);
}
