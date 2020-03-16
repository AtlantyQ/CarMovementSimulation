#include "CVechicleManager.h"
#include "CVechicleModel.h"
#include "Qt"
#include <QtDebug>
#include <QTimer>
#include <QMetaObject>

#define logDebug( arg ) printf( arg )

CVehicleManager::CVehicleManager() : m_Thread( &CVehicleManager::worker_thread, this ),
                                                        isRunning(true)
{
}

void CVehicleManager::CreatePrototypes( QWidget* parent )
{
    m_CarPrototypes[VehicleType::FORD]     = std::make_unique<CVehicleModel>( new CVehicleModel( "FORD", "#F4F4F4", { 0.02, 0.05, 0.001 }, 100, parent) );
    m_CarPrototypes[VehicleType::MUSTANG]  = std::make_unique<CVehicleModel>(  new CVehicleModel( "MUSTANG", "#F4F4F4", { 0.02, 0.05, 0.001 }, 100, parent) );
    m_CarPrototypes[VehicleType::FERRARI]  = std::make_unique<CVehicleModel>(  new CVehicleModel( "FERRARI", "#F4F4F4", { 0.02, 0.05, 0.0001 }, 100, parent) );
    m_CarPrototypes[VehicleType::BMW]      = std::make_unique<CVehicleModel>(  new CVehicleModel( "BMW", "#F4F4F4", { 0.02, 0.05, 0.001 }, 100, parent ) );
    m_CarPrototypes[VehicleType::AUDI]     = std::make_unique<CVehicleModel>(  new CVehicleModel( "AUDI", "#F4F4F4", { 00.2, 0.05, 0.001 }, 100, parent) );
    m_CarPrototypes[VehicleType::MERCEDES] = std::make_unique<CVehicleModel>(  new CVehicleModel( "MERCEDES", "#F4F4F4", { 0.02, 0.05, 0.001 }, 100, parent) );
    m_CarPrototypes[VehicleType::ALFA]     = std::make_unique<CVehicleModel>(  new CVehicleModel( "ALFA", "#F4F4F4", { 0.02, 0.05, 0.001 }, 100, parent) );
    m_CarPrototypes[VehicleType::FIAT]     = std::make_unique<CVehicleModel>(  new CVehicleModel( "FIAT", "#F4F4F4", { 0.02, 0.05, 0.001 }, 100, parent) );

    m_Thread.detach();
}

CVehicleManager::~CVehicleManager()
{
    isRunning = false;
    m_Thread.join();
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
    m_VehiclesQueue.push_back( std::make_unique<CVehicleModel>(static_cast<CVehicleModel*>(m_CarPrototypes[id]->getClone())));

    //cv.notify_one();
}

void CVehicleManager::worker_thread()
{
    while(isRunning)
    {
        if(m_VehiclesQueue.empty())
        {
            std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
            continue;
        }

        //std::unique_lock<std::mutex> mlck( m_CarQueueMtx );
        //cv.wait( mlck, [&]{ return !m_VehiclesQueue.empty(); } );

        m_CarQueueMtx.lock();
        for( auto vehicle = m_VehiclesQueue.begin(); vehicle != m_VehiclesQueue.end(); ++vehicle )
        {
            if( IsAboutToCrash( vehicle ) )
            {
               // QMetaObject::invokeMethod( vehicle->get(), "stop", Qt::QueuedConnection );//GUI have to be updated from main thread
            }
            else
            {
                QMetaObject::invokeMethod( vehicle->get(), "move", Qt::QueuedConnection );
            }

            if( (*vehicle)->getPos().x >= FINAL_POINT )
            {
                m_VehiclesQueue.erase( vehicle );
                vehicle--;
            }
        }
        m_CarQueueMtx.unlock();
        //mlck.unlock();
    }
}

bool CVehicleManager::IsAboutToCrash(VehicleQueue::iterator vehicle)
{
    if(  m_VehiclesQueue.size() > 0 && vehicle == m_VehiclesQueue.begin() )
        return false;

    VehicleQueue::iterator currentVehicle = vehicle;
    VehicleQueue::iterator nextVehicle = std::prev( vehicle );

    double currVehPosition = (*currentVehicle)->getPos().x;
    double nextVehPosition = (*nextVehicle)->getPos().x;

    if( ( nextVehPosition - currVehPosition ) > MAX_DISTANCE )
    {
        return true;
    }

    return false;
}
