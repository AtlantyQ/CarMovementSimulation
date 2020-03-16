#ifndef IVehicleINTERFACE_H
#define IVehicleINTERFACE_H

#include <QObject>

enum class VehicleType : int
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
    double x;
    double y;
} Position;

class IVehicleModel : public QObject
{
    Q_OBJECT
public:
    IVehicleModel( QObject* parent = nullptr ) : QObject( parent ){}
    virtual ~IVehicleModel() = default;

    virtual void setPos( const Position& positon ) = 0;
    virtual Position getPos() const = 0;
    virtual IVehicleModel* getClone() = 0;
public slots:
    virtual void move() = 0;
    virtual void stop() = 0;
    virtual void hide() = 0;
};


#endif // IVehicleINTERFACE_H
