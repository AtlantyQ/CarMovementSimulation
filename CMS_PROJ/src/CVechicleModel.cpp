#include "CVechicleModel.h"
#include <cmath>
#include <QDebug>
#include <QString>
#include <QMetaObject>
#include <CWidgetFactory.h>

#define PI 3.14159265
#define ANGLE 0
#define STYLE_SHEET "background-color: #F4F4F4; border-style: solid; border-color: black"


CVehicleModel::CVehicleModel(  std::string type, std::string color, Factor factor, int maxSpeed, QWidget* parent ) : m_Car( nullptr )
                                                                                                                   , m_SpeedVal( nullptr )
                                                                                                                   , m_Factory( new CWidgetFactory )
                                                                                                                   , m_CarPosition{ 0, 480}
                                                                                                                   , m_CarType( type )
                                                                                                                   , m_Factor(factor)
                                                                                                                   , m_MaxSpeed( maxSpeed )

{
    m_Car = m_Factory->MakeWidgetFrame( { parent, STYLE_SHEET, { 80, 40 }, {0, 480} }, false );
    m_SpeedVal = m_Factory->MakeLabelFrame( { m_Car, { 80, 40 }, { 20, 0 } }, false );
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

CVehicleModel::CVehicleModel( CVehicleModel& x )
{
    qDebug() << " CVehicleModel& x";
    QWidget* parent = static_cast<QWidget*>( x.m_Car->parent() );

    this->m_Car = m_Factory->MakeWidgetFrame( { parent, STYLE_SHEET, { 80, 40 }, {0, 480 } } );
    this->m_SpeedVal = m_Factory->MakeLabelFrame( { this->m_Car, { 80, 40 }, { 20, 0 } } );
    this->m_CarPosition = { 0, 480 };
    this->m_Factor = x.m_Factor;
    this->m_MaxSpeed = x.m_MaxSpeed;
}

CVehicleModel::CVehicleModel( CVehicleModel* x )
{
    qDebug() << " CVehicleModel* x";
    QWidget* parent = static_cast<QWidget*>( x->m_Car->parent() );

    this->m_Car = m_Factory->MakeWidgetFrame( { parent, STYLE_SHEET, { 80, 40 }, {0, 480} } );
    this->m_SpeedVal = m_Factory->MakeLabelFrame( { this->m_Car, { 80, 40 }, { 20, 0 } } );
    this->m_CarPosition = { 0, 480 };
    this->m_Factor = x->m_Factor;
    this->m_MaxSpeed = x->m_MaxSpeed;
}

CVehicleModel& CVehicleModel::operator=( CVehicleModel& x )
{
    qDebug() << " operator= &x";
    QWidget* parent = static_cast<QWidget*>( x.m_Car->parent() );

    this->m_Car = m_Factory->MakeWidgetFrame( { parent, STYLE_SHEET, { 80, 40 }, {0, 480} } );
    this->m_SpeedVal = m_Factory->MakeLabelFrame( { this->m_Car, { 80, 40 }, { 20, 0 } } );
    this->m_CarPosition = { 0, 480 };
    this->m_Factor = x.m_Factor;
    this->m_MaxSpeed = x.m_MaxSpeed;

    return x;
}

void CVehicleModel::move()
{
    m_Timer.start();
    double dt = m_Timer.elapsed()/1000.0;
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
    double dt = m_Timer.elapsed()/1000.0;
    double x0 = 2 * m_Factor.a + m_Factor.b;
    double f1 = m_Factor.a  + m_Factor.b + m_Factor.c;
    double speed = -1/x0 * dt + f1 * x0;

    double dx = 1 * speed;
    double dy = 0 * speed;

    m_CarPosition.x += dx;
    m_CarPosition.y += dy;
    this->setPos( m_CarPosition );

    //http://zdajmyrazem.pl/Main/Theory/rownanie-stycznej-do-wykresu-funkcji-NTE5NA%3D%3D
    //https://matfiz24.pl/funkcja-liniowa/prosta-prostopadla-rownolegla-zadania
}

void CVehicleModel::hide()
{
    m_Car->hide();
}

double CVehicleModel::calculateSpeed( double dt )
{
    double speed = m_Factor.a * dt * dt + m_Factor.b * dt + m_Factor.c;

    //if( speed > m_MaxSpeed )
    //    speed = m_MaxSpeed;

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

IVehicleModel* CVehicleModel::getClone()
{
    return new CVehicleModel( *this );
}

Position CVehicleModel::getPos() const
{
    return m_CarPosition;
}







