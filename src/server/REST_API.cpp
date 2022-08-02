#include "REST_API.h"

using QtJson::JsonObject;
using QtJson::JsonArray;

REST_API::REST_API( MainLogic *listener )
{
    mainLogic = listener;
    hardware = mainLogic->getPlatformHWInstance();
    camera = mainLogic->getCameraInstance();
}

QString REST_API::processZoom( QHttpRequestHeader header, QString body )
{
    QString responseHeader = getResponseHeader( 404 ).toString();
    QString responseBody;

    if( header.method().compare( "GET" ) == 0 )
    {
        responseBody = QString::number( camera->getZoomValue() );
        responseHeader = getResponseHeader( 200, responseBody.size(),
                                            mediaType.toMIME( "text/plain" ))
                .toString();
    }
    else if( header.method().compare( "PUT" ) == 0 )
    {
        bool ok;
        JsonObject result = QtJson::parse( body, ok ).toMap();
        if( !ok )
        {
            qWarning() << "An error occurred during parsing";
            return getResponseHeader( 400 ).toString();
        }

        float value = result[ "value" ].toFloat( &ok );
        if( !ok )
        {
            qWarning() << "Missing parameter";
            return getResponseHeader( 400 ).toString();
        }

        camera->setZoomDirect( value );

        return getResponseHeader( 200 ).toString();
    }

    return responseHeader + responseBody;
}

QString REST_API::processZoomLock( QHttpRequestHeader header, QString )
{
    QString responseHeader = getResponseHeader( 404 ).toString();
    QString responseBody;

    if( header.method().compare( "GET" ) == 0 )
    {
        responseBody = QString::number( camera->getZoomLocked() );
        responseHeader = getResponseHeader( 200, responseBody.size(),
                                            mediaType.toMIME( "text/plain" ))
                .toString();
    }
    else if( header.method().compare( "POST" ) == 0 )
    {
        camera->setZoomLocked( 1 );
        responseHeader = getResponseHeader( 200 ).toString();
    }
    else if( header.method().compare( "PUT" ) == 0 )
    {
        camera->setZoomLocked( !camera->getZoomLocked() );
        responseHeader = getResponseHeader( 200 ).toString();
    }
    else if( header.method().compare( "DELETE" ) == 0 )
    {
        camera->setZoomLocked( 0 );
        responseHeader = getResponseHeader( 200 ).toString();
    }

    return responseHeader + responseBody;
}

QString REST_API::processMagnification( QHttpRequestHeader header,
                                           QString body )
{
    QString responseHeader = getResponseHeader( 404 ).toString();
    QString responseBody;

    if( header.method().compare( "GET" ) == 0 )
    {
        quint16 zoom = camera->getZoomValue();
        responseBody = QString::number( camera->getMagnification( zoom ) );
        responseHeader = getResponseHeader( 200, responseBody.size(),
                                            mediaType.toMIME( "text/plain" ))
                .toString();
    }
    else if( header.method().compare( "PUT" ) == 0 )
    {
        bool ok;
        JsonObject result = QtJson::parse( body, ok ).toMap();
        if( !ok )
        {
            qWarning() << "An error occurred during parsing";
            return getResponseHeader( 400 ).toString();
        }

        float value = result[ "value" ].toFloat( &ok );
        if( !ok )
        {
            qWarning() << "Missing parameter";
            return getResponseHeader( 400 ).toString();
        }

        camera->setMagnification( value );

        return getResponseHeader( 200 ).toString();
    }

    return responseHeader + responseBody;
}

QString REST_API::processFocus( QHttpRequestHeader header, QString body )
{
    QString responseHeader = getResponseHeader( 404 ).toString();
    QString responseBody;

    if( header.method().compare( "GET" ) == 0 )
    {
        responseBody = QString::number( camera->getFocusValue() );
        responseHeader = getResponseHeader( 200, responseBody.size(),
                                            mediaType.toMIME( "text/plain" ))
                .toString();
    }
    else if( header.method().compare( "PUT" ) == 0 )
    {
        bool ok;
        JsonObject result = QtJson::parse( body, ok ).toMap();
        if( !ok )
        {
            qWarning() << "An error occurred during parsing";
            return getResponseHeader( 400 ).toString();
        }

        float value = result[ "value" ].toFloat( &ok );
        if( !ok )
        {
            qWarning() << "Missing parameter";
            return getResponseHeader( 400 ).toString();
        }

        camera->setFocusDirect( value );

        return getResponseHeader( 200 ).toString();
    }

    return responseHeader + responseBody;
}

QString REST_API::processFocusAuto( QHttpRequestHeader header, QString )
{
    QString responseHeader = getResponseHeader( 404 ).toString();
    QString responseBody;

    if( header.method().compare( "GET" ) == 0 )
    {
        responseBody = QString::number( camera->getAutofocus() );
        responseHeader = getResponseHeader( 200, responseBody.size(),
                                            mediaType.toMIME( "text/plain" ))
                .toString();
    }
    else if( header.method().compare( "POST" ) == 0 )
    {
        camera->setAutofocus( true );
        responseHeader = getResponseHeader( 200 ).toString();
    }
    else if( header.method().compare( "PUT" ) == 0 )
    {
        camera->setAutofocus( !camera->getAutofocus() );
        responseHeader = getResponseHeader( 200 ).toString();
    }
    else if( header.method().compare( "DELETE" ) == 0 )
    {
        camera->setAutofocus( false );
        responseHeader = getResponseHeader( 200 ).toString();
    }

    return responseHeader + responseBody;
}

QString REST_API::processLed( QHttpRequestHeader header, QString )
{
    QString responseHeader = getResponseHeader( 404 ).toString();
    QString responseBody;

    if( header.method().compare( "GET" ) == 0 )
    {
        responseBody = QString::number( hardware->getLedPowerState() );
        responseHeader = getResponseHeader( 200, responseBody.size(),
                                            mediaType.toMIME( "text/plain" ))
                .toString();
    }
    else if( header.method().compare( "POST" ) == 0 )
    {
        hardware->setLedPowerState( 1 );
        responseHeader = getResponseHeader( 200 ).toString();
    }
    else if( header.method().compare( "PUT" ) == 0 )
    {
        hardware->toggleLedPowerState();
        responseHeader = getResponseHeader( 200 ).toString();
    }
    else if( header.method().compare( "DELETE" ) == 0 )
    {
        hardware->setLedPowerState( 0 );
        responseHeader = getResponseHeader( 200 ).toString();
    }

    return responseHeader + responseBody;
}

QString REST_API::processLaser( QHttpRequestHeader header, QString )
{
    QString responseHeader = getResponseHeader( 404 ).toString();
    QString responseBody;

    if( header.method().compare( "GET" ) == 0 )
    {
        responseBody = QString::number( hardware->getLaserPowerState() );
        responseHeader = getResponseHeader( 200, responseBody.size(),
                                            mediaType.toMIME( "text/plain" ))
                .toString();
    }
    else if( header.method().compare( "POST" ) == 0 )
    {
        hardware->setLaserPowerState( 1 );
        responseHeader = getResponseHeader( 200 ).toString();
    }
    else if( header.method().compare( "PUT" ) == 0 )
    {
        hardware->toggleLaserPowerState();
        responseHeader = getResponseHeader( 200 ).toString();
    }
    else if( header.method().compare( "DELETE" ) == 0 )
    {
        hardware->setLaserPowerState( 0 );
        responseHeader = getResponseHeader( 200 ).toString();
    }

    return responseHeader + responseBody;
}

QString REST_API::processIRfilter( QHttpRequestHeader header, QString )
{
    QString responseHeader = getResponseHeader( 404 ).toString();
    QString responseBody;

    if( header.method().compare( "POST" ) == 0 )
    {
        camera->setIrMode( false );
        responseHeader = getResponseHeader( 200 ).toString();
    }
    else if( header.method().compare( "DELETE" ) == 0 )
    {
        camera->setIrMode( true );
        responseHeader = getResponseHeader( 200 ).toString();
    }

    return responseHeader + responseBody;
}

QString REST_API::processPictureFlip( QHttpRequestHeader header, QString )
{
    QString responseHeader = getResponseHeader( 404 ).toString();
    QString responseBody;

    if( header.method().compare( "POST" ) == 0 )
    {
        camera->setPictureFlip( true );
        responseHeader = getResponseHeader( 200 ).toString();
    }
    else if( header.method().compare( "DELETE" ) == 0 )
    {
        camera->setPictureFlip( false );
        responseHeader = getResponseHeader( 200 ).toString();
    }

    return responseHeader + responseBody;
}

QByteArray REST_API::processImage( QHttpRequestHeader header, QString,
                                   QString imageName )
{
    QByteArray responseHeader = getResponseHeader( 404 ).toString().toUtf8();
    QByteArray responseBody;

    if( header.method().compare( "GET" ) == 0 )
    {
        if( imageName.isEmpty() )
        {
            QImage tmp = imageCapture.captureCameraVideoBufferToQImage();
            QBuffer buffer( &responseBody );
            buffer.open( QIODevice::WriteOnly );
            tmp.save( &buffer, "png", 100 );

            responseHeader = getResponseHeader( 200, responseBody.size(),
                                                mediaType.toMIME( "png" ) )
                              .toString().toUtf8();
        }
        else
        {
            QFile file( "/tmp/usbstick/" + imageName );
            if( !file.open( QIODevice::ReadOnly ) )
            {
                qWarning() << "File not found";
            }
            else
            {
                responseBody = file.readAll();
                file.close();

                responseHeader = getResponseHeader( 200, responseBody.size(),
                                                    mediaType.toMIME( "png" ) )
                                    .toString().toUtf8();
            }
        }
    }
    else if( header.method().compare( "POST" ) == 0 )
    {
        if( !imageName.isEmpty() )
        {
            imageCapture.captureImage( "/tmp/usbstick/" + imageName,
                                       false );
            responseHeader = getResponseHeader( 200 ).toString().toUtf8();
        }
    }
    else if( header.method().compare( "DELETE" ) == 0 )
    {
        if( !imageName.isEmpty() )
        {
            QFile file( "/tmp/usbstick/" + imageName );
            if( !file.open( QIODevice::ReadOnly ) )
            {
                qWarning() << "File not found";
            }
            else
            {
                file.remove();

                responseHeader = getResponseHeader( 200 ).toString().toUtf8();
            }
        }
    }

    return responseHeader + responseBody;
}

QString REST_API::processMeta( QHttpRequestHeader header )
{
    QString responseHeader = getResponseHeader( 404 ).toString();
    QString responseBody;

    if( header.method().compare( "GET" ) == 0 )
    {
        QFile file( "/tmp/usbstick/meta.txt" );
        if( !file.open( QIODevice::ReadOnly ) )
        {
            qWarning() << "File not found";
        }
        else
        {
            responseBody = file.readAll();
            file.close();

            responseHeader = getResponseHeader( 200, responseBody.size(),
                                                mediaType.toMIME( "text/plain" ))
                    .toString();
        }
    }

    return responseHeader + responseBody;
}

QString REST_API::processFocusStack( QHttpRequestHeader header, QString body )
{
    QString responseHeader = getResponseHeader( 404 ).toString();
    QString responseBody;

    if( header.method().compare( "POST" ) == 0 )
    {
        bool ok;
        JsonObject result = QtJson::parse( body, ok ).toMap();
        if( !ok )
        {
            qWarning() << "An error occurred during parsing";
            return getResponseHeader( 400 ).toString();
        }

        bool p1, p2, p3, p4;
        int zoom = result["zoom"].toInt( &p1 );
        int minFocus = result["minfocus"].toInt( &p2 );
        int maxFocus = result["maxfocus"].toInt( &p3 );
        int steps = result["steps"].toInt( &p4 );

        if( !p1 + !p2 + !p3 + !p4 )
        {
            qWarning() << "Missing parameter";
            return getResponseHeader( 400 ).toString();
        }

        if( steps < 2 )
        {
            qWarning() << "Not enough steps";
            return getResponseHeader( 400 ).toString();
        }

        // Enable zoom and autofocus
        bool zoomLocked = camera->getZoomLocked();
        uint8_t autofocus = camera->getAutofocus();
        uint16_t zoomValue = camera->getZoomValue();
        uint16_t focusValue = camera->getFocusValue();
        camera->setZoomLocked( false );
        camera->setAutofocus( false );
        qDebug() << "Enabled zoom and autofocus";

        // Set zoom
        camera->setZoomDirect( zoom );
        while( camera->getZoomValue() != zoom ) {}
        qDebug() << "Set zoom" << zoom;

        // Calculate focus step
        int step = ( maxFocus - minFocus ) / ( steps - 1 );
        qDebug() << "Step: " << step;

        responseBody = QString::number( zoom ) + "\n";

        uint16_t currentFocus = minFocus;
        for( int i = 0; i < steps; i++ )
        {
            camera->setFocusDirect( currentFocus );
            while( camera->getFocusValue() != currentFocus ) {};
            usleep( 1000 );

            QString fileName = QString::number( i ) + ".png";
            imageCapture.captureImage( "/tmp/usbstick/" + fileName,
                                       false );
            usleep( 1000 );

            qDebug() << fileName << " " << camera->getFocusValue();
            responseBody += fileName + " " +
                    QString::number( camera->getFocusValue() ) +
                    " " + QString::number( hardware->getLedPowerState() ) +
                    "\n";

            currentFocus += step;
        }

        // Initialize meta file
        QFile file( "/tmp/usbstick/meta.txt" );
        file.open( QIODevice::WriteOnly );
        QTextStream meta( &file );
        meta << responseBody;
        file.close();
        qDebug() << "Created meta file";

        // Restore parameters
        qDebug() << "Restore zoom and focus";
        camera->setZoomDirect( zoomValue );
        camera->setFocusDirect( focusValue );
        while( camera->getFocusValue() != focusValue ||
               camera->getZoomValue() != zoomValue ) {};
        camera->setZoomLocked( zoomLocked );
        camera->setAutofocus( autofocus );

        responseHeader = getResponseHeader( 200, responseBody.size(),
                                            mediaType.toMIME( "text/plain" ))
                .toString();
    }

    return responseHeader + responseBody;
}

QHttpResponseHeader REST_API::getResponseHeader( quint16 responseCode,
                                                 int contentLength,
                                                 QString contentType )
{
    QHttpResponseHeader toReturn( responseCode );
    if( !contentType.isEmpty() )
    {
        toReturn.setContentType( contentType );
    }
    toReturn.setContentLength( contentLength );
    toReturn.setValue( "server", "TAGARNO FHD Uno" );
    return toReturn;
}
