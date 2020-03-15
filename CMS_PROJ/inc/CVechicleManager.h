#ifndef CVECHICLEMANAGER_H
#define CVECHICLEMANAGER_H

#include <QObject>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <vector>
#include <map>
#include "IVechicleManager.h"

typedef std::vector<std::unique_ptr<IVechicleModel>> VechicleQueue;

class CVechicleManager : public IVechicleManager
{
public:
    CVechicleManager( QObject* parent = nullptr );
    virtual ~CVechicleManager();
    void AddNextVechicleToQueue();

private:
    IVechicleModel* GetCarPrototype( VechicleType id );
    void worker_thread();

    std::map< VechicleType, std::unique_ptr<IVechicleModel> > m_CarPrototypes;
    std::mutex m_CarQueueMtx;
    std::mutex m_CarPrototypeMtx;
    VechicleQueue m_VechiclesQueue;
    std::condition_variable cv;
    std::thread m_Thread;
    bool isRunning;

    static constexpr int FINAL_POINT = 800;
};

#endif // CVECHICLEMANAGER_H

