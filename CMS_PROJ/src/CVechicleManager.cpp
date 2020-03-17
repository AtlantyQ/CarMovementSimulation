#include "CVechicleManager.h"
#include "CVechicleModel.h"
#include <QTimer>
#include <QMetaObject>
#include <future>

CVehicleManager::CVehicleManager()
{
}

void CVehicleManager::CreatePrototypes( QWidget* parent )
{
    m_CarPrototypes[VehicleType::FORD]     = std::make_unique<CVehicleModel>( CVehicleModel( "FORD", "background-color: #666666;", { 0.015, 0.5, 1.4 }, 100, parent) );
    m_CarPrototypes[VehicleType::MUSTANG]  = std::make_unique<CVehicleModel>( CVehicleModel( "MUSTANG", "background-color: #468499;", { 0.036, 0.5, 1.1 }, 100, parent) );
    m_CarPrototypes[VehicleType::FERRARI]  = std::make_unique<CVehicleModel>( CVehicleModel( "FERRARI", "background-color: #990000;", { 0.22, 0.5, 2.3 }, 100, parent) );
    m_CarPrototypes[VehicleType::BMW]      = std::make_unique<CVehicleModel>( CVehicleModel( "BMW", "background-color: #ffdab9;", { 0.15, 0.5, 1.25 }, 100, parent ) );
    m_CarPrototypes[VehicleType::AUDI]     = std::make_unique<CVehicleModel>( CVehicleModel( "AUDI", "background-color: #4ca3dd;", { 0.013, 0.5, 1.15 }, 100, parent) );
    m_CarPrototypes[VehicleType::MERCEDES] = std::make_unique<CVehicleModel>( CVehicleModel( "MERCEDES", "background-color: #6897bb;", { 0.02, 0.5, 1.12 }, 100, parent) );
    m_CarPrototypes[VehicleType::ALFA]     = std::make_unique<CVehicleModel>( CVehicleModel( "ALFA", "background-color: #ff4040;", { 0.11, 0.5, 1.01 }, 100, parent) );
    m_CarPrototypes[VehicleType::FIAT]     = std::make_unique<CVehicleModel>( CVehicleModel( "FIAT", "background-color: #a0db8e;", { 0.13, 0.5, 1.01 }, 100, parent) );

    for(auto& vechicle : m_CarPrototypes )
    {
        vechicle.second.get()->hide();
    }

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
    m_VehiclesQueue.push_back( std::make_unique<CVehicleModel>( *(static_cast<CVehicleModel*>(m_CarPrototypes[id]->getClone())) ));
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
    for( auto vehicle = m_VehiclesQueue.begin(); vehicle != m_VehiclesQueue.end(); ++vehicle )
    {
        if( IsAboutToCrash( vehicle ) )
        {
            QMetaObject::invokeMethod( vehicle->get(), "stop", Qt::DirectConnection );//GUI have to be updated from main thread
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

bool CVehicleManager::IsAboutToCrash( VehicleQueue::iterator currentVehicle )
{
    double currVehPosition = (*currentVehicle)->getPos().x;

    for( auto& nextVehicle : m_VehiclesQueue )
    {
        if( nextVehicle->getPos().x > currVehPosition )
        {
            double nextVehPosition = nextVehicle->getPos().x;

            if( ( nextVehPosition - currVehPosition ) < MIN_ALLOWED_DISTANCE )
            {
                return true;
            }
        }
    }

    return false;
}
