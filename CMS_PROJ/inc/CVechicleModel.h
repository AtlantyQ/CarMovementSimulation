#ifndef CVECHICLECONTROLER_H
#define CVECHICLECONTROLER_H

#include <QWidget>
#include <QLabel>
#include <string>
#include <utility>
#include <Qt>
#include <memory>
#include "IVechicleInterface.h"

class CVechicleModel : public IVechicleModel
{
    Q_OBJECT

public:
    CVechicleModel( std::string type, Qt::GlobalColor color, double factor, int maxSpeed, const QObject* parent = nullptr );
    CVechicleModel( CVechicleModel& x );
    CVechicleModel& operator=( CVechicleModel& x );
    virtual ~CVechicleModel();

    void move();
    void setPos( const Position& positon );
    Position getPos() const;
    IVechicleModel* getClone();

private:
    Position calculateMovement( const int dt );

//Private members

    QWidget* m_Car;
    QLabel m_Speed;
    Position m_CarPosition;
    VechicleType m_CarType;
    std::string m_CarName;

    int m_Factor;
    int m_MaxSpeed;

};

#endif // CVECHICLECONTROLER_H
