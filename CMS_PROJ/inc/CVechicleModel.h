#ifndef CVehicleCONTROLER_H
#define CVehicleCONTROLER_H

#include <QWidget>
#include <QLabel>
#include <string>
#include <utility>
#include <memory>
#include "CTimer.h"
#include "IVechicleInterface.h"

class CWidgetFactory;

typedef struct
{
    double a;
    double b;
    double c;
} Factor;

class CVehicleModel : public IVehicleModel
{
    Q_OBJECT

public:
    CVehicleModel( std::string type, std::string color, Factor factor, int maxSpeed, QWidget* parent = nullptr );
    CVehicleModel( CVehicleModel& x );
    CVehicleModel( CVehicleModel&& x );
    CVehicleModel& operator=( CVehicleModel& x );
    virtual ~CVehicleModel();


    void setPos( const Position& positon ) override ;
    Position getPos() const override;
    IVehicleModel* getClone() override;

public slots:
    void move() override;
    void stop() override;
    void hide() override;

private:
    double calculateSpeed( const double dt );
    void setSpeedValue( double speed );

    QWidget* m_Car;
    QLabel* m_SpeedVal;
    CWidgetFactory* m_Factory;
    Position m_CarPosition;
    std::string m_CarType;
    std::string m_Color;
    Timer m_Timer;
    Factor m_Factor;
    double m_MaxSpeed;
};

#endif // CVehicleCONTROLER_H

