#include "CMainWindow.h"
#include "CVechicleControler.h"
#include "random"

#define TIMEOUT( min, max ) min + std::rand() % ( (max + 1) - min )

CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize( 800, 800 );
    this->setStyleSheet("background-color: #FFFFFF;");

    m_CarPrototypes[VechicleType::FORD]     = std::unique_ptr<IVechicleCtrl>( new CVechicleCtrl( "FORD", 0.65, 100, this) );
    m_CarPrototypes[VechicleType::MUSTANG]  = std::unique_ptr<IVechicleCtrl>( new CVechicleCtrl( "MUSTANG", 0.65, 100, this) );
    m_CarPrototypes[VechicleType::FERRARI]  = std::unique_ptr<IVechicleCtrl>( new CVechicleCtrl( "FERRARI", 0.65, 100, this) );
    m_CarPrototypes[VechicleType::BMW]      = std::unique_ptr<IVechicleCtrl>( new CVechicleCtrl( "BMW", 0.65, 100, this) );
    m_CarPrototypes[VechicleType::AUDI]     = std::unique_ptr<IVechicleCtrl>( new CVechicleCtrl( "AUDI", 0.65, 100, this) );
    m_CarPrototypes[VechicleType::MERCEDES] = std::unique_ptr<IVechicleCtrl>( new CVechicleCtrl( "MERCEDES", 0.65, 100, this) );
    m_CarPrototypes[VechicleType::ALFA]     = std::unique_ptr<IVechicleCtrl>( new CVechicleCtrl( "ALFA", 0.65, 100, this) );
    m_CarPrototypes[VechicleType::FIAT]     = std::unique_ptr<IVechicleCtrl>( new CVechicleCtrl( "FIAT", 0.65, 100, this) );

    m_Timer.setTimerType( Qt::PreciseTimer );
    m_Timer.singleShot( 200, this, SLOT(sltTimeout()) );
}

CMainWindow::~CMainWindow()
{
}

void CMainWindow::sltTimeout()
{
    int nextTimeout = TIMEOUT( minTimeout, maxTimeout );
    m_Timer.singleShot( nextTimeout, this, SLOT(sltTimeout()) );
}

IVechicleCtrl* CMainWindow::getCarPrototype( VechicleType id )
{
    std::lock_guard<std::mutex> lock( m_CarPrototypeMtx );

    return m_CarPrototypes[id]->getClone();
}

void CMainWindow::CreateVechicle()
{
    auto getVechicleId = []() -> VechicleType
    {
        int range = static_cast<int>( VechicleType::MAX );
        VechicleType id = static_cast<VechicleType>( std::rand() % range );
        return id;
    };

    VechicleType id = getVechicleId();
    std::unique_ptr<IVechicleCtrl> vechicleCtrl = std::make_unique<IVechicleCtrl>( this->getCarPrototype( id ) );
}


