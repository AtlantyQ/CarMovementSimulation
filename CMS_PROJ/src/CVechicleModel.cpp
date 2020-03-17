#include "CVechicleModel.h"
#include <cmath>
#include <QMetaObject>
#include <CWidgetFactory.h>

#define PI 3.14159265
#define ANGLE 0


CVehicleModel::CVehicleModel(  std::string type, std::string color, Factor factor, int maxSpeed, QWidget* parent ) : IVehicleModel( nullptr )
                                                                                                                   , m_Car( nullptr )
                                                                                                                   , m_SpeedVal( nullptr )
                                                                                                                   , m_Factory( new CWidgetFactory )
                                                                                                                   , m_CarPosition{ 0, 480}
                                                                                                                   , m_CarType( type )
                                                                                                                   , m_Factor(factor)
                                                                                                                   , m_MaxSpeed( maxSpeed )
                                                                                                                   , m_dtMv(0.0)
                                                                                                                   , m_dtStop(0.0)

{
    m_Car = m_Factory->MakeWidgetFrame( { parent, color, { 80, 40 }, {0, 480} }, false );
    m_Car->hide();
    m_SpeedVal = m_Factory->MakeLabelFrame( { m_Car, { 80, 40 }, { 15, 0 } }, false );
    m_SpeedVal->hide();
}

CVehicleModel::~CVehicleModel()
{
    if( m_Car )
    {
        m_Car->deleteLater();
        m_Car = nullptr;
    }

    if( m_SpeedVal )
    {
        m_SpeedVal->deleteLater();
        m_SpeedVal = nullptr;
    }
}

CVehicleModel::CVehicleModel( CVehicleModel&& x ) : IVehicleModel( nullptr )
                                                  , m_Car( nullptr )
                                                  , m_SpeedVal( nullptr )
                                                  , m_Factory( new CWidgetFactory )
                                                  , m_CarPosition{ 0, 480}
                                                  , m_CarType()
                                                  , m_Factor({ 0.f, 0.f, 0.f})
                                                  , m_MaxSpeed( 0 )
                                                  , m_dtMv(0.0)
                                                  , m_dtStop(0.0)

{
    QWidget* parent = static_cast<QWidget*>( x.m_Car->parent() );

    this->m_Car = m_Factory->MakeWidgetFrame( { parent, x.m_Car->styleSheet().toStdString(), { 80, 40 }, {0, 480 } } );
    this->m_SpeedVal = m_Factory->MakeLabelFrame( { this->m_Car, { 80, 40 }, { 15, 0 } } );
    this->m_CarPosition = { 0, 480 };
    this->m_Factor = x.m_Factor;
    this->m_MaxSpeed = x.m_MaxSpeed;
    this->m_CarType = x.m_CarType;
}

CVehicleModel::CVehicleModel( CVehicleModel& x ) : IVehicleModel( nullptr )
                                                 , m_Car( nullptr )
                                                 , m_SpeedVal( nullptr )
                                                 , m_Factory( new CWidgetFactory )
                                                 , m_CarPosition{ 0, 480}
                                                 , m_CarType()
                                                 , m_Factor({ 0.f, 0.f, 0.f})
                                                 , m_MaxSpeed( 0 )
                                                 , m_dtMv(0.0)
                                                 , m_dtStop(0.0)

{
    QWidget* parent = static_cast<QWidget*>( x.m_Car->parent() );

    this->m_Car = m_Factory->MakeWidgetFrame( { parent, x.m_Car->styleSheet().toStdString(), { 80, 40 }, {0, 480 } } );
    this->m_SpeedVal = m_Factory->MakeLabelFrame( { this->m_Car, { 80, 40 }, { 15, 0 } } );
    this->m_CarPosition = { 0, 480 };
    this->m_Factor = x.m_Factor;
    this->m_MaxSpeed = x.m_MaxSpeed;
    this->m_CarType = x.m_CarType;
}

CVehicleModel& CVehicleModel::operator=( CVehicleModel& x )
{
    QWidget* parent = static_cast<QWidget*>( x.m_Car->parent() );

    this->m_Car = m_Factory->MakeWidgetFrame( { parent, x.m_Car->styleSheet().toStdString(), { 80, 40 }, {0, 480} } );
    this->m_SpeedVal = m_Factory->MakeLabelFrame( { this->m_Car, { 80, 40 }, { 15, 0 } } );
    this->m_CarPosition = { 0, 480 };
    this->m_Factor = x.m_Factor;
    this->m_MaxSpeed = x.m_MaxSpeed;
    this->m_CarType = x.m_CarType;

    return x;
}

void CVehicleModel::move()
{
    m_Timer.SetStartPoint();
    m_Timer.start();

    double diff = m_Timer.elapsed() - m_Timer.GetStartPoint();
    double dt = ( m_Timer.GetDelta() + diff )/1000.f;
    double speed = this->calculateSpeed( dt );
    double dx = std::cos( ANGLE * PI/180 ) * speed;
    double dy = std::sin( ANGLE * PI/180 ) * speed;

    m_CarPosition.x += dx;
    m_CarPosition.y += dy;
    this->setPos( m_CarPosition );
    this->setSpeedValue( speed );
}

void CVehicleModel::stop()
{    
    m_Timer.SetStopPoint();
    m_Timer.start();

    double diff = m_Timer.elapsed() - m_Timer.GetStopPoint();
    double dt = ( m_Timer.GetStopPoint() - diff )/1000.f;
    double speed = this->calculateSpeed( dt );
    double dx = std::cos( ANGLE * PI/180 ) * speed;
    double dy = std::sin( ANGLE * PI/180 ) * speed;


    m_Timer.SetDeltaTime( dt );
    m_CarPosition.x += dx;
    m_CarPosition.y += dy;

    this->setPos( m_CarPosition );
    this->setSpeedValue( speed );
}

void CVehicleModel::hide()
{
    m_Car->hide();
}

double CVehicleModel::calculateSpeed( double dt )
{
    double speed = m_Factor.a * dt * dt + m_Factor.b * dt + m_Factor.c;

    if( speed < 0 ) return 0;

    return speed;
}

void CVehicleModel::setPos( const Position& positon  )
{
    m_Car->move(  positon.x, positon.y );
}

void CVehicleModel::setSpeedValue( double speed )
{
    std::string speedTxt = std::to_string( speed * 10 ).substr(0, 5) + std::string(" km/h");
    m_SpeedVal->setText( speedTxt.c_str() );
}

Position CVehicleModel::getPos() const
{
    return m_CarPosition;
}

IVehicleModel* CVehicleModel::getClone()
{
    return this;
}








