#ifndef REST_SERVER_H
#define REST_SERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QNetworkInterface>
#include <QHttpRequestHeader>
#include "REST_API.h"

#include <QDebug>

class REST_Server : QObject
{
    Q_OBJECT

public:
    explicit REST_Server( MainLogic *listener, QObject *parent = 0 );
    ~REST_Server();

private slots:
    void newClient();
    void readClient();

private:
    QString getBody( QString request );

    QTcpServer *tcpServer;
    QMap<int, QTcpSocket*> SClients;
    REST_API *api;
};

#endif // REST_SERVER_H
