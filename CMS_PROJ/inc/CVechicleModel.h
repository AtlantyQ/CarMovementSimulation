#ifndef CVehicleCONTROLER_H
#define CVehicleCONTROLER_H

#include <QWidget>
#include <QLabel>
#include <QElapsedTimer>
#include <string>
#include <utility>
#include <Qt>
#include <memory>
#include "IVechicleInterface.h"

class CWidgetFactory;


class Timer : public QElapsedTimer
{
public:
    Timer() : isRunning(false){}
    ~Timer() = default;

    void start()
    {
        if(!isStarted())
        {
            QElapsedTimer::start();
            isRunning = true;
        }
    }

    bool isStarted() { return isRunning; }

private:
    bool isRunning;
};

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
    CVehicleModel( CVehicleModel* x );
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
    Timer m_Timer;
    Factor m_Factor;
    double m_MaxSpeed;

};

#endif // CVehicleCONTROLER_H
