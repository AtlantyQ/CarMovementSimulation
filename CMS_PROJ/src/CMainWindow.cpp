#include <Qt>
#include "CMainWindow.h"
#include "CVechicleManager.h"
#include "random"

#define RAND_TIMEOUT( min, max ) min + std::rand() % ( (max + 1) - min )

CMainWindow::CMainWindow( QWidget *parent ) : QMainWindow( parent ),
                                              m_VechicleCtrl( new CVechicleManager( this ) )
{
    int timeout = RAND_TIMEOUT( minTimeout, maxTimeout );

    this->setFixedSize( 1200, 800 );
    this->setStyleSheet("background-color: #FFFFFF;");

    m_Timer.setTimerType( Qt::PreciseTimer );
    m_Timer.singleShot( timeout, this, SLOT(AddNextVechicleToQueue()) );
}

CMainWindow::~CMainWindow()
{
}


void CMainWindow::sltTimeOut()
{
    int nextTimeout = RAND_TIMEOUT( minTimeout, maxTimeout );

    m_VechicleCtrl->AddNextVechicleToQueue();
    m_Timer.singleShot( nextTimeout, this, SLOT(sltTimeOut()) );
}


