#ifndef REST_API_H
#define REST_API_H

#include "JSON.h"
#include "MediaType.h"
#include "mainlogic.h"
#include "UserModeControl.h"
#include "ViscaCamera.h"
#include "ImageCapture.h"

class REST_API
{
public:
    REST_API( MainLogic *listener );

    /*!
     * \brief Process <b>/zoom</b> according to the instruction table.
     * \param header Request header
     * \param body Request body
     * \return HTTP response (header + body)
     */
    QString processZoom( QHttpRequestHeader header, QString body );
    /*!
     * \brief Process <b>/zoom/lock</b> according to the instruction table.
     * \param header Request header
     * \param body Request body
     * \return HTTP response (header + body)
     */
    QString processZoomLock( QHttpRequestHeader header, QString body );
    /*!
     * \brief Process <b>/magnification</b> according to the instruction table.
     * \param header Request header
     * \param body Request body
     * \return HTTP response (header + body)
     */
    QString processMagnification( QHttpRequestHeader header, QString body );
    /*!
     * \brief Process <b>/focus</b> according to the instruction table.
     * \param header Request header
     * \param body Request body
     * \return HTTP response (header + body)
     */
    QString processFocus( QHttpRequestHeader header, QString body );
    /*!
     * \brief Process <b>/focus/auto</b> according to the instruction table.
     * \param header Request header
     * \param body Request body
     * \return HTTP response (header + body)
     */
    QString processFocusAuto( QHttpRequestHeader header, QString body );
    /*!
     * \brief Process <b>/led</b> according to the instruction table.
     * \param header Request header
     * \param body Request body
     * \return HTTP response (header + body)
     */
    QString processLed( QHttpRequestHeader header, QString body );
    /*!
     * \brief Process <b>/laser</b> according to the instruction table.
     * \param header Request header
     * \param body Request body
     * \return HTTP response (header + body)
     */
    QString processLaser( QHttpRequestHeader header, QString body );
    /*!
     * \brief Process <b>/ir</b> according to the instruction table.
     * \param header Request header
     * \param body Request body
     * \return HTTP response (header + body)
     */
    QString processIRfilter( QHttpRequestHeader header, QString body );
    /*!
     * \brief Process <b>/flip</b> according to the instruction table.
     * \param header Request header
     * \param body Request body
     * \return HTTP response (header + body)
     */
    QString processPictureFlip( QHttpRequestHeader header, QString body );
    /*!
     * \brief Process <b>/image/___.___</b> according to the instruction table.
     * \param header Request header
     * \param body Request body
     * \param imageName Required image name
     * \return HTTP response (header + body)
     */
    QByteArray processImage( QHttpRequestHeader header, QString body,
                             QString imageName = "" );
    /*!
     * \brief Process <b>/meta</b> according to the instruction table.
     * \param header Request header
     * \param body Request body
     * \return HTTP response (header + body)
     */
    QString processMeta( QHttpRequestHeader header );
    /*!
     * \brief Process <b>/focusstack</b> according to the instruction table.
     * \param header Request header
     * \param body Request body
     * \return HTTP response (header + body)
     */
    QString processFocusStack( QHttpRequestHeader header, QString body );

private:
    QHttpResponseHeader getResponseHeader( quint16 responseCode,
                                           int contentLength = 0,
                                           QString contentType = "" );
    MediaType &mediaType = MediaType::Instance();
    MainLogic *mainLogic;
    PlatformHW *hardware;
    ViscaCamera *camera;
    ImageCapture imageCapture;
};

#endif // REST_API_H
