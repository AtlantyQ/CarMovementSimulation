#include "CVechicleModel.h"
#include <cmath>
#include <QDebug>
#include <QMetaObject>
#define logDebug( arg,... ) printf( arg )
#define PI 3.14159265

CVehicleModel::CVehicleModel(  std::string type, std::string color, Factor factor, int maxSpeed, QWidget* parent ) : m_Car( new QWidget( parent ) )
                                                                                                                        , m_parent(parent)
                                                                                                                        , m_Speed( new QLabel( "0 km/h", parent ))
                                                                                                                        , m_CarPosition{ 0, 480}
                                                                                                                        , m_CarType( type )
                                                                                                                        , m_Factor(factor)
                                                                                                                        , m_MaxSpeed( maxSpeed )

{
    m_Car->setStyleSheet("background-color: #F4F4F4; border-style: solid; border-color: black");
    m_Car->setFixedSize( 80, 40 );
    m_Car->move( m_CarPosition.x, m_CarPosition.y );
}

CVehicleModel::~CVehicleModel()
{
    //qDebug() << "~CVehicleModel()\n";
    if( m_Car )
    {
        //qDebug() << "~m_Car()\n";
        m_Car->hide();
        m_Car->deleteLater();
        m_Car = nullptr;
    }

    if( m_Speed )
    {
        //qDebug() << "~m_Speed()\n";
        m_Speed->hide();
        m_Speed->deleteLater();
        m_Speed = nullptr;
    }
    //qDebug() << "~CVehicleModel() return\n";
}

CVehicleModel::CVehicleModel( CVehicleModel& x )
{
    QWidget* parent = static_cast<QWidget*>( x.m_Car->parent() );
    ///@TODO: Make Factory Method
    this->m_Car = new QWidget( parent );
    this->m_Car->setStyleSheet( x.m_Car->styleSheet() );
    this->m_Car->setFixedSize( x.m_Car->size() );
    this->m_Car->show();

    this->m_Speed = new QLabel( "0 km/h", this->m_Car );
    this->m_Speed->setFixedSize( 80, 40 );
    this->m_Speed->move( 25, 0 );
    this->m_Speed->show();

    this->m_CarPosition = {0, 480};
    this->m_Factor = x.m_Factor;
    this->m_MaxSpeed = x.m_MaxSpeed;
}

CVehicleModel::CVehicleModel( CVehicleModel* x )
{
    QWidget* parent = dynamic_cast<QWidget*>( x->m_Car->parent() );
    //assert( !parent );

    this->m_Car = new QWidget( parent );
    this->m_Car->setStyleSheet( x->m_Car->styleSheet() );
    this->m_Car->setFixedSize( x->m_Car->size() );
    this->m_Car->show();

    this->m_Speed = new QLabel( "0 km/h", this->m_Car );
    this->m_Speed->setFixedSize( 80, 40 );
    this->m_Speed->move( 25, 0);
    this->m_Speed->show();

    this->m_CarPosition = {0, 480};
    this->m_Factor = x->m_Factor;
    this->m_MaxSpeed = x->m_MaxSpeed;
}

CVehicleModel& CVehicleModel::operator=( CVehicleModel& x )
{
    QWidget* parent = dynamic_cast<QWidget*>( x.m_Car->parent() );
    assert( !parent );

    this->m_Car = new QWidget( parent );
    this->m_Car->show();

    this->m_Speed = new QLabel( "0 km/h", this->m_Car );
    this->m_Speed->move( 25, 0 );
    this->m_Speed->setFixedSize( 80, 40 );
    this->m_Speed->show();

    m_CarPosition = {0, 480};
    m_Factor = x.m_Factor;
    m_MaxSpeed = x.m_MaxSpeed;

    return x;
}

void CVehicleModel::move()
{
    m_Timer.start();
    double dt = m_Timer.elapsed()/100000.0;
    double speed = this->calculateSpeed( dt );
    double dx = 1 * speed;
    double dy = 0 * speed;

    m_CarPosition.x += dx;
    m_CarPosition.y += dy;

    this->setPos( m_CarPosition );
    this->setSpeedValue( speed );
}

void CVehicleModel::stop()
{
    double dt = m_Timer.elapsed()/100000.0;
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

    if( speed > m_MaxSpeed )
        speed = m_MaxSpeed;

    return speed;
}

void CVehicleModel::setPos( const Position& positon  )
{
    m_Car->move( positon.x, positon.y );
}

void CVehicleModel::setSpeedValue( double speed )
{
    //std::string speedTxt = std::to_string( speed * 100000 ).substr(0, 5) + std::string(" km/h");
    //m_Speed->setText( speedTxt.c_str() );
}

IVehicleModel* CVehicleModel::getClone()
{
    return new CVehicleModel( *this );
}

Position CVehicleModel::getPos() const
{
    return m_CarPosition;
}







