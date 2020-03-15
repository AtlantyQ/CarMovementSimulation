#include "CVechicleManager.h"
#include "CVechicleModel.h"
#include "Qt"


#define logDebug( arg ) printf( arg )

CVechicleManager::CVechicleManager() : m_Thread( &CVechicleManager::worker_thread, this ),
                                                        isRunning(true)
{
}

void CVechicleManager::CreatePrototypes( QWidget* parent )
{
    m_CarPrototypes[VechicleType::FORD]     = std::make_unique<CVechicleModel>( new CVechicleModel( "FORD", Qt::blue, 4, 100, parent ));
    m_CarPrototypes[VechicleType::MUSTANG]  = std::make_unique<CVechicleModel>( new CVechicleModel( "MUSTANG", Qt::darkBlue, 4, 100, parent) );
    m_CarPrototypes[VechicleType::FERRARI]  = std::make_unique<CVechicleModel>( new CVechicleModel( "FERRARI", Qt::red, 4, 100, parent) );
    m_CarPrototypes[VechicleType::BMW]      = std::make_unique<CVechicleModel>( new CVechicleModel( "BMW", Qt::darkGray, 4, 100, parent) );
    m_CarPrototypes[VechicleType::AUDI]     = std::make_unique<CVechicleModel>( new CVechicleModel( "AUDI", Qt::black, 4, 100, parent) );
    m_CarPrototypes[VechicleType::MERCEDES] = std::make_unique<CVechicleModel>( new CVechicleModel( "MERCEDES", Qt::gray, 4, 100, parent) );
    m_CarPrototypes[VechicleType::ALFA]     = std::make_unique<CVechicleModel>( new CVechicleModel( "ALFA", Qt::darkRed, 4, 100, parent) );
    m_CarPrototypes[VechicleType::FIAT]     = std::make_unique<CVechicleModel>( new CVechicleModel( "FIAT", Qt::darkYellow, 4, 100, parent) );

    for( auto& prototype : m_CarPrototypes )
    {
        //prototype.second->hide();
    }

    m_Thread.detach();
}

CVechicleManager::~CVechicleManager()
{
    isRunning = false;
    m_Thread.join();
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
    if(m_VechiclesQueue.empty())
        m_VechiclesQueue.push_back( std::make_unique<CVechicleModel>(static_cast<CVechicleModel*>(m_CarPrototypes[id]->getClone())));
    cv.notify_one();
}

void CVechicleManager::worker_thread()
{
    while(isRunning)
    {
        std::unique_lock<std::mutex> mlck( m_CarQueueMtx );
        cv.wait( mlck, [&]{ return !m_VechiclesQueue.empty(); } );

        for( auto vechicle = m_VechiclesQueue.begin(); vechicle != m_VechiclesQueue.end(); ++vechicle )
        {
            logDebug("(*vechicle)->move()\n");
            (*vechicle)->move();

            if( (*vechicle)->getPos().y >= FINAL_POINT )
            {
                m_VechiclesQueue.erase( vechicle );
                vechicle--;
            }
        }
        mlck.unlock();
    }
}
