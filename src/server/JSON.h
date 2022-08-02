#ifndef JSON_H
#define JSON_H

#include <QVariant>
#include <QString>

namespace QtJson
{
typedef QVariantMap JsonObject;
typedef QVariantList JsonArray;

QVariant clone( const QVariant &data );

void insert( QVariant &v, const QString &key, const QVariant &value );

void append( QVariant &v, const QVariant &value );

QVariant parse( const QString &json );
QVariant parse( const QString &json, bool &success );

QByteArray serialize( const QVariant &data );
QByteArray serialize( const QVariant &data, bool &success );
QString serializeStr( const QVariant &data );
QString serializeStr( const QVariant &data, bool &success );

void setDateTimeFormat( const QString& format );
void setDateFormat( const QString& format );
QString getDateTimeFormat();
QString getDateFormat();

class Object : public QVariant
{
    template<typename T>
    Object& insertKey( Object* ptr, const QString& key )
    {
        T* p = (T*)ptr->data();
        if ( !p->contains( key ) ) p->insert( key, QVariant() );
        return *reinterpret_cast<Object*>( &p->operator[]( key ) );
    }

    template<typename T>
    void removeKey( Object *ptr, const QString& key )
    {
        T* p = (T*)ptr->data();
        p->remove( key );
    }

public:
    Object() : QVariant() {}
    Object( const Object& ref ) : QVariant( ref ) {}

    Object& operator = ( const QVariant& rhs )
    {
        QObject *obj = qvariant_cast<QObject *>( rhs );
        setValue(obj);
        return *this;
    }

    Object& operator[](const QString& key)
    {
        if( type() == QVariant::Map )
        {
            return insertKey<QVariantMap>( this, key );
        }
        else if( type() == QVariant::Hash )
        {
            return insertKey<QVariantHash>( this, key );
        }

        setValue( QVariantMap() );

        return insertKey<QVariantMap>( this, key );
    }

    const Object& operator[]( const QString& key ) const
    {
        return const_cast<Object*>( this )->operator[]( key );
    }

    void remove( const QString& key )
    {
        if( type() == QVariant::Map )
        {
            removeKey<QVariantMap>( this, key );
        }
        else if( type() == QVariant::Hash )
        {
            removeKey<QVariantHash>( this, key );
        }
    }
};
}

#endif //JSON_H
