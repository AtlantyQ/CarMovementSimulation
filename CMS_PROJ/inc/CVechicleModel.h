#ifndef CVECHICLECONTROLER_H
#define CVECHICLECONTROLER_H

#include <QWidget>
#include <QLabel>
#include <QElapsedTimer>
#include <string>
#include <utility>
#include <Qt>
#include <memory>
#include "IVechicleInterface.h"


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
} Factor;

class CVechicleModel : public IVechicleModel
{
    Q_OBJECT

public:
    CVechicleModel( std::string type, Qt::GlobalColor color, double factor, int maxSpeed, QWidget* parent = nullptr );
    CVechicleModel( CVechicleModel& x );
    CVechicleModel( CVechicleModel* x );
    CVechicleModel& operator=( CVechicleModel& x );
    virtual ~CVechicleModel();

    void move();
    void stop();
    void hide();
    void setPos( const Position& positon );
    Position getPos() const;
    IVechicleModel* getClone();

private:
    double calculateMovement( const double dt );

//Private members

    QWidget* m_Car;
    QWidget* m_parent;
    QLabel* m_Speed;
    Position m_CarPosition;
    std::string m_CarType;
    Timer m_Timer;
    Factor m_Factor;
    int m_MaxSpeed;

};

#endif // CVECHICLECONTROLER_H
