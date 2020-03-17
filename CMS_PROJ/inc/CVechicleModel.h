#ifndef CVehicleCONTROLER_H
#define CVehicleCONTROLER_H

#include <QWidget>
#include <QLabel>
#include <string>
#include <utility>
#include <CTimer.h>
#include <memory>
#include "IVechicleInterface.h"

#include <QDebug>
#include <QString>

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


    void setPos( const Position& positon );
    void setSpeedValue( double speed );
    Position getPos() const;
    IVehicleModel* getClone();

public slots:
    void move();
    void stop();
    void hide();

private:
    double calculateSpeed( const double dt );

    QWidget* m_Car;
    QLabel* m_SpeedVal;
    CWidgetFactory* m_Factory;
    Position m_CarPosition;
    std::string m_CarType;
    std::string m_Color;
    Timer m_Timer;
    Factor m_Factor;
    double m_MaxSpeed;
    double m_deltaTimeMv;
    double m_dtMv;
    double m_dtStop;
};

#endif // CVehicleCONTROLER_H

