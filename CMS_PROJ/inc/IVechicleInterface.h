#ifndef IVECHICLEINTERFACE_H
#define IVECHICLEINTERFACE_H

#include <QObject>

typedef enum
{
    VT_FORD = 0x00,
    VT_MUSTANG = 0x01,
    VT_FERRARI = 0x02,
    VT_FIAT = 0x03,
} VechicleType;

typedef enum
{
    LINEAR = 0x00,
    LOGARYTHMIC = 0x01,
} Veliocity;


class IVechicleCtrl : public QObject
{
    Q_OBJECT
public:
    IVechicleCtrl( QObject* parent = 0 ) : QObject( parent ){}
    ~IVechicleCtrl();

    virtual void move( int dt) = 0;
};


#endif // IVECHICLEINTERFACE_H
