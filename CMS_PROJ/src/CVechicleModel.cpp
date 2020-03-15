#include "CVechicleModel.h"

#define logDebug( arg,... ) printf( arg )

CVechicleModel::CVechicleModel( std::string type, Qt::GlobalColor color, double factor, int maxSpeed, QWidget* parent ) : m_Car( new QWidget( parent ) )
                                                                                                                        , m_parent(parent)
                                                                                                                        , m_Speed( new QLabel( "0 km/h", parent ))
                                                                                                                        , m_CarPosition{400, 0}
                                                                                                                        , m_CarType( type )
                                                                                                                        , m_Factor{ factor, 0}
                                                                                                                        , m_MaxSpeed( maxSpeed )

{
    m_Car->setStyleSheet("background-color: #F4F4F4; border-style: solid; border-color: black");
    m_Car->setFixedSize( 80, 140 );
    m_Car->move( m_CarPosition.x, m_CarPosition.y );
    //m_Car->show();

}

CVechicleModel::~CVechicleModel()
{
    m_Car->deleteLater();

}

CVechicleModel::CVechicleModel( CVechicleModel& x )
{
    QWidget* parent = static_cast<QWidget*>( x.m_Car->parent() );
    //assert( !parent );

    this->m_Car = new QWidget( parent );
    this->m_Car->setStyleSheet("background-color: #F4F4F4; border-style: solid; border-color: black");
    this->m_Car->setFixedSize( 80, 140 );
    this->m_Car->show();

    this->m_Speed = new QLabel( "0 km/h", parent );
    this->m_Speed->show();

    this->m_CarPosition = {480, 0};
    this->m_Factor = x.m_Factor;
    this->m_MaxSpeed = x.m_MaxSpeed;
}

CVechicleModel::CVechicleModel( CVechicleModel* x )
{
    QWidget* parent = dynamic_cast<QWidget*>( x->m_Car->parent() );
    //assert( !parent );

    this->m_Car = new QWidget( parent );
    this->m_Car->setStyleSheet("background-color: #F4F4F4; border-style: solid; border-color: black");
    this->m_Car->setFixedSize( 80, 140 );
    this->m_Car->show();

    this->m_Speed = new QLabel( "0 km/h", parent );
    this->m_Speed->show();

    this->m_CarPosition = {480, 0};
    this->m_Factor = x->m_Factor;
    this->m_MaxSpeed = x->m_MaxSpeed;
}

CVechicleModel& CVechicleModel::operator=( CVechicleModel& x )
{
    QWidget* parent = dynamic_cast<QWidget*>( x.m_Car->parent() );
    assert( !parent );

    m_Car = new QWidget( parent );
    this->m_Car->show();
    m_Speed = new QLabel( "0 km/h", parent );
    this->m_Speed->show();
    m_CarPosition = {480, 0};
    m_Factor = x.m_Factor;
    m_MaxSpeed = x.m_MaxSpeed;

    return x;
}

void CVechicleModel::move()
{
    m_Timer.start();

    double dt = m_Timer.elapsed()/100;
    printf( "dt: %d dt/1000: %f \n", m_Timer.elapsed(), dt );
    m_CarPosition.x = 480;
    m_CarPosition.y = this->calculateMovement( dt );
    printf( "m_CarPosition x: %f y: %f\n", m_CarPosition.x, m_CarPosition.y );
    setPos( m_CarPosition );
}

void CVechicleModel::stop()
{

}

void CVechicleModel::hide()
{
    m_Car->hide();
}

double CVechicleModel::calculateMovement( double dt )
{
    return m_Factor.a * dt + m_Factor.b;
}

void CVechicleModel::setPos( const Position& positon  )
{
    m_Car->show();
    m_Car->move( positon.x, positon.y );
}

IVechicleModel* CVechicleModel::getClone()
{
    return new CVechicleModel( *this );
}

Position CVechicleModel::getPos() const
{
    return m_CarPosition;
}







