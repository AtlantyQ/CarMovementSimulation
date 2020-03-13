#ifndef IVECHICLEINTERFACE_H
#define IVECHICLEINTERFACE_H

#include <QObject>

enum class VechicleType : int
{
    FORD = 0x00,
    MUSTANG,
    FERRARI,
    BMW,
    AUDI,
    MERCEDES,
    ALFA,
    FIAT,
    MAX
};

typedef struct
{
    int x;
    int y;
} Position;

class IVechicleCtrl : public QObject
{
    Q_OBJECT
public:
    IVechicleCtrl( QObject* parent = 0 ) : QObject( parent ){}
    ~IVechicleCtrl(){}

    virtual void move( int dt) = 0;
    virtual void setPos( const Position& positon ) = 0;
    virtual Position getPos() const = 0;
    virtual IVechicleCtrl* getClone() = 0;
};


#endif // IVECHICLEINTERFACE_H
