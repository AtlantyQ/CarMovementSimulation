#ifndef CVECHICLECONTROLER_H
#define CVECHICLECONTROLER_H

#include <QWidget>
#include <string>
#include <utility>
#include <memory>
#include "IVechicleInterface.h"

class CVechicleCtrl : public IVechicleCtrl
{
    Q_OBJECT

public:
    CVechicleCtrl( std::string type, double factor, int maxSpeed, const QObject* parent = nullptr );
    CVechicleCtrl( CVechicleCtrl& x );
    CVechicleCtrl& operator=( CVechicleCtrl& x );
    ~CVechicleCtrl();

    void move( const int dt );
    void setPos( const Position& positon );
    Position getPos() const;
    IVechicleCtrl* getClone();

private:
    Position calculateMovement( const int dt );

//Private members

    QWidget m_Car;
    Position m_CarPosition;
    VechicleType m_CarType;
    std::string m_CarName;

    int m_Factor;
    int m_MaxSpeed;

};

#endif // CVECHICLECONTROLER_H
