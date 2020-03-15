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
    double x;
    double y;
} Position;

class IVechicleModel : public QObject
{
    Q_OBJECT
public:
    IVechicleModel( QObject* parent = nullptr ) : QObject( parent ){}
    virtual ~IVechicleModel() = default;

    virtual void move() = 0;
    virtual void stop() = 0;
    virtual void hide() = 0;
    virtual void setPos( const Position& positon ) = 0;
    virtual Position getPos() const = 0;
    virtual IVechicleModel* getClone() = 0;
};


#endif // IVECHICLEINTERFACE_H
