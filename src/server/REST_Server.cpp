#include "REST_Server.h"
#include "JSON.h"

using QtJson::JsonObject;
using QtJson::JsonArray;

REST_Server::REST_Server( MainLogic *listener, QObject *parent )
    : QObject( parent ), tcpServer(0)
{
    api = new REST_API( listener );
    tcpServer = new QTcpServer(this);

    if( !tcpServer->listen( QHostAddress::Any, 80 ) )
    {
        qDebug() << QString( "Unable to start the server: %1." )
                    .arg( tcpServer->errorString() );
        return;
    }
    else
    {
        // Print information about the running server
        foreach( const QHostAddress &address, QNetworkInterface::allAddresses() )
        {
            if( address != QHostAddress::LocalHost && address.toIPv4Address())
            {
                qDebug() << QString( "REST API is running.\nIPv4: %1\nPORT: %2" )
                            .arg( address.toString() )
                            .arg( tcpServer->serverPort() );

                break;
            }
        }
    }

    connect( tcpServer, SIGNAL( newConnection() ),
             this, SLOT( newClient() ) );
}

REST_Server::~REST_Server()
{
    delete api;
    delete tcpServer;
}

void REST_Server::newClient()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    int idusersocs = clientSocket->socketDescriptor();

    qDebug() << "User ID: " << idusersocs;

    SClients[ idusersocs ] = clientSocket;
    connect( clientSocket, SIGNAL( readyRead() ),
             this, SLOT( readClient() ));
}

void REST_Server::readClient()
{
    QTcpSocket *clientSocket = reinterpret_cast<QTcpSocket*>( sender() );
    int idusersocs = clientSocket->socketDescriptor();
    QTextStream os( clientSocket );
    os.setAutoDetectUnicode( true );

    QString request = clientSocket->readAll();
    QHttpRequestHeader requestHeader( request );
    QString requestBody = getBody( request );

    qDebug() << requestHeader.path();

    if( requestHeader.path().compare( "/zoom" ) == 0 )
    {
        os << api->processZoom( requestHeader, requestBody );
    }
    else if( requestHeader.path().compare( "/zoom/lock" ) == 0 )
    {
        os << api->processZoomLock( requestHeader, requestBody );
    }
    else if( requestHeader.path().compare( "/magnification" ) == 0 )
    {
        os << api->processMagnification( requestHeader, requestBody );
    }
    else if( requestHeader.path().compare( "/focus" ) == 0 )
    {
        os << api->processFocus( requestHeader, requestBody );
    }
    else if( requestHeader.path().compare( "/focus/auto" ) == 0 )
    {
        os << api->processFocusAuto( requestHeader, requestBody );
    }
    else if( requestHeader.path().compare( "/led" ) == 0 )
    {
        os << api->processLed( requestHeader, requestBody );
    }
    else if( requestHeader.path().compare( "/laser" ) == 0 )
    {
        os << api->processLaser( requestHeader, requestBody );
    }
    else if( requestHeader.path().compare( "/ir" ) == 0 )
    {
        os << api->processIRfilter( requestHeader, requestBody );
    }
    else if( requestHeader.path().compare( "/flip" ) == 0 )
    {
        os << api->processPictureFlip( requestHeader, requestBody );
    }
    else if( requestHeader.path().startsWith("/image") )
    {
        QString imageName = requestHeader.path().right( requestHeader.path().length()
                                                        - requestHeader.path().startsWith("/image/")
                                                        - 6 );
        os << api->processImage( requestHeader, requestBody, imageName );
    }
    else if( requestHeader.path().compare( "/meta" ) == 0 )
    {
        os << api->processMeta( requestHeader );
    }
    else if( requestHeader.path().compare( "/focusstack" ) == 0 )
    {
        os << api->processFocusStack( requestHeader, requestBody );
    }
    else
    {
        QHttpResponseHeader response( 404 );
        response.setValue( "server", "TAGARNO FHD Uno" );
        os <<response.toString();
    }

    clientSocket->close();
    SClients.remove( idusersocs );
}

QString REST_Server::getBody( QString request )
{
    int bodyIndex = request.indexOf(QString( "\r\n\r\n" ) ) + 4;
    return request.right( request.length() - bodyIndex );
}
