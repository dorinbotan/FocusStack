#ifndef MEDIATYPE_H
#define MEDIATYPE_H

#include <QMap>
#include <QString>

class MediaType
{
public:
    static MediaType& Instance();
    MediaType( MediaType const& ) = delete;
    void operator = ( MediaType const& ) = delete;

    QString toMIME( QString format );

private:
    MediaType();
    QMap<QString, QString> map;
};

#endif // MEDIATYPE_H
