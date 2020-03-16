#include "CVechicleManager.h"
#include "CVechicleModel.h"
#include "Qt"
#include <QtDebug>
#include <QTimer>
#include <QMetaObject>

CVehicleManager::CVehicleManager()
{
}

void CVehicleManager::CreatePrototypes( QWidget* parent )
{
    m_CarPrototypes[VehicleType::FORD]     = std::make_unique<CVehicleModel>( new CVehicleModel( "FORD", "#F4F4F4", { 0.02, 0.5, 0.1 }, 100, parent) );
    m_CarPrototypes[VehicleType::MUSTANG]  = std::make_unique<CVehicleModel>(  new CVehicleModel( "MUSTANG", "#F4F4F4", { 0.02, 0.5, 0.1 }, 100, parent) );
    m_CarPrototypes[VehicleType::FERRARI]  = std::make_unique<CVehicleModel>(  new CVehicleModel( "FERRARI", "#F4F4F4", { 0.02, 0.5, 0.1 }, 100, parent) );
    m_CarPrototypes[VehicleType::BMW]      = std::make_unique<CVehicleModel>(  new CVehicleModel( "BMW", "#F4F4F4", { 0.02, 0.5, 0.1 }, 100, parent ) );
    m_CarPrototypes[VehicleType::AUDI]     = std::make_unique<CVehicleModel>(  new CVehicleModel( "AUDI", "#F4F4F4", { 0.02, 0.5, 0.1 }, 100, parent) );
    m_CarPrototypes[VehicleType::MERCEDES] = std::make_unique<CVehicleModel>(  new CVehicleModel( "MERCEDES", "#F4F4F4", { 0.02, 0.5, 0.1 }, 100, parent) );
    m_CarPrototypes[VehicleType::ALFA]     = std::make_unique<CVehicleModel>(  new CVehicleModel( "ALFA", "#F4F4F4", { 0.02, 0.5, 0.1 }, 100, parent) );
    m_CarPrototypes[VehicleType::FIAT]     = std::make_unique<CVehicleModel>(  new CVehicleModel( "FIAT", "#F4F4F4", { 0.02, 0.5, 0.1 }, 100, parent) );

    QTimer::singleShot( 1000 , this, SLOT(AsyncWorkerCaller()) );
}

CVehicleManager::~CVehicleManager()
{
}

void CVehicleManager::AddNextVehicleToQueue()
{
    auto getRandomVehicleId = []() -> VehicleType
    {
        int range = static_cast<int>( VehicleType::MAX );
        VehicleType id = static_cast<VehicleType>( std::rand() % range );
        return id;
    };
    VehicleType id = getRandomVehicleId();

    std::lock_guard<std::mutex> mlck( m_CarQueueMtx );
    m_VehiclesQueue.push_back( std::make_unique<CVehicleModel>( static_cast<CVehicleModel*>(m_CarPrototypes[id]->getClone()) ) );
}

void CVehicleManager::AsyncWorkerCaller()
{
    auto f = std::async( std::launch::async, &CVehicleManager::worker, this );
    f.get();
    QTimer::singleShot( 10, this, SLOT( AsyncWorkerCaller() ) );
}

void CVehicleManager::worker()
{
    std::lock_guard<std::mutex> mlck( m_CarQueueMtx );
    //qDebug() << QString("m_VehiclesQueue: %1 \n").arg(m_VehiclesQueue.size());
    for( auto vehicle = m_VehiclesQueue.begin(); vehicle != m_VehiclesQueue.end(); ++vehicle )
    {
        if( IsAboutToCrash( vehicle, (vehicle - 1) ) )
        {
            //QMetaObject::invokeMethod( vehicle->get(), "stop", Qt::DirectConnection );//GUI have to be updated from main thread
        }
        else
        {
            QMetaObject::invokeMethod( vehicle->get(), "move", Qt::DirectConnection );
        }

        if( (*vehicle)->getPos().x >= FINAL_POINT )
        {
            m_VehiclesQueue.erase( vehicle );
            vehicle--;
        }
    }
}

bool CVehicleManager::IsAboutToCrash(VehicleQueue::iterator currentVehicle, VehicleQueue::iterator nextVehicle)
{
    if( currentVehicle == m_VehiclesQueue.begin() )
        return false;

    double currVehPosition = (*currentVehicle)->getPos().x;
    double nextVehPosition = (*nextVehicle)->getPos().x;

    if( ( nextVehPosition - currVehPosition ) < MAX_DISTANCE )
    {
        return true;
    }

    return false;
}
