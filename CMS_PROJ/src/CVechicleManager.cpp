#include "CVechicleManager.h"
#include "CVechicleModel.h"
#include "Qt"




CVechicleManager::CVechicleManager( QObject* parent ) : m_Thread( &CVechicleManager::worker_thread, this ),
                                                        isRunning(true)
{
    m_CarPrototypes[VechicleType::FORD]     = std::make_unique<IVechicleModel>( new CVechicleModel( "FORD", Qt::blue, 0.65, 100, parent) );
    m_CarPrototypes[VechicleType::MUSTANG]  = std::make_unique<IVechicleModel>( new CVechicleModel( "MUSTANG", Qt::darkBlue, 0.65, 100, parent) );
    m_CarPrototypes[VechicleType::FERRARI]  = std::make_unique<IVechicleModel>( new CVechicleModel( "FERRARI", Qt::red, 0.65, 100, parent) );
    m_CarPrototypes[VechicleType::BMW]      = std::make_unique<IVechicleModel>( new CVechicleModel( "BMW", Qt::darkGray, 0.65, 100, parent) );
    m_CarPrototypes[VechicleType::AUDI]     = std::make_unique<IVechicleModel>( new CVechicleModel( "AUDI", Qt::black, 0.65, 100, parent) );
    m_CarPrototypes[VechicleType::MERCEDES] = std::make_unique<IVechicleModel>( new CVechicleModel( "MERCEDES", Qt::gray, 0.65, 100, parent) );
    m_CarPrototypes[VechicleType::ALFA]     = std::make_unique<IVechicleModel>( new CVechicleModel( "ALFA", Qt::darkRed, 0.65, 100, parent) );
    m_CarPrototypes[VechicleType::FIAT]     = std::make_unique<IVechicleModel>( new CVechicleModel( "FIAT", Qt::darkYellow, 0.65, 100, parent) );

    m_Thread.detach();
}

CVechicleManager::~CVechicleManager()
{

}

IVechicleModel* CVechicleManager::GetCarPrototype( VechicleType id )
{
    return m_CarPrototypes[id]->getClone();
}

void CVechicleManager::AddNextVechicleToQueue()
{
    std::lock_guard<std::mutex> mlck( m_CarQueueMtx );
    auto getRandomVechicleId = []() -> VechicleType
    {
        int range = static_cast<int>( VechicleType::MAX );
        VechicleType id = static_cast<VechicleType>( std::rand() % range );
        return id;
    };

    VechicleType id = getRandomVechicleId();
    m_VechiclesQueue.push_back( std::make_unique<IVechicleModel>( m_CarPrototypes[id]->getClone() ) );
    cv.notify_one();
}

void CVechicleManager::worker_thread()
{
    while(true)
    {
        std::unique_lock<std::mutex> mlck( m_CarQueueMtx );
        cv.wait( mlck, [&]{ return !m_VechiclesQueue.empty(); } );

        for( auto vechicle = m_VechiclesQueue.begin(); vechicle != m_VechiclesQueue.end(); ++vechicle )
        {
            (*vechicle)->move();

            if( (*vechicle)->getPos().y >= FINAL_POINT )
            {
                m_VechiclesQueue.erase( vechicle );
            }
        }

        mlck.unlock();
    }
}
