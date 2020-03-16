#include <Qt>
#include "CMainWindow.h"
#include "CVechicleManager.h"
#include "random"
#include <QDebug>

#define RAND_TIMEOUT( min, max ) min + std::rand() % ( (max + 1) - min )

CMainWindow::CMainWindow( QWidget *parent ) : QMainWindow( parent ),
                                              m_VehicleCtrl( new CVehicleManager )
{
    int timeout = RAND_TIMEOUT( minTimeout, maxTimeout );

    this->setFixedSize( 850, 600 );
    this->setStyleSheet("background-color: #FFFFFF;");

    m_Timer.setTimerType( Qt::PreciseTimer );
    m_Timer.singleShot( 1000, this, SLOT(TimeOut()) );
}

void CMainWindow::show()
{
    QMainWindow::show();
    m_VehicleCtrl->CreatePrototypes( this );
}

void CMainWindow::TimeOut()
{
    qDebug() << "TimeOut ";
    int nextTimeout = RAND_TIMEOUT( minTimeout, maxTimeout );

    m_VehicleCtrl->AddNextVehicleToQueue();
    m_Timer.singleShot( nextTimeout, this, SLOT(TimeOut()) );
}


