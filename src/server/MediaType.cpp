#include "MediaType.h"

MediaType& MediaType::Instance()
{
    static MediaType instance;
    return instance;
}

MediaType::MediaType()
{
    map[ "js" ]   = "application/javascript; charset=utf-8";
    map[ "json" ] = "application/json; charset=utf-8";
    map[ "ico" ]  = "image/x-icon";
    map[ "svg" ]  = "image/svg+xml";
    map[ "png" ]  = "image/png";
    map[ "jpg" ]  = "image/jpeg";
    map[ "tiff" ] = "image/tiff";
    map[ "html" ] = "text/html; charset=utf-8";
    map[ "css" ]  = "text/css; charset=utf-8";
    map[ "text/plain" ]  = "text/plain; charset=utf-8";
}

QString MediaType::toMIME( QString format ) { return map[ format ]; }
