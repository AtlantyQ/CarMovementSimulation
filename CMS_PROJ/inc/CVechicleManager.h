#ifndef CVECHICLEMANAGER_H
#define CVECHICLEMANAGER_H

#include <QObject>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <vector>
#include <map>
#include "IVechicleManager.h"
#include "IVechicleInterface.h"

typedef std::vector<std::unique_ptr<IVechicleModel>> VechicleQueue;
typedef std::map< VechicleType, std::unique_ptr<IVechicleModel> > VechicleMap;

class CVechicleManager : public IVechicleManager
{
public:
    CVechicleManager();
    virtual ~CVechicleManager();
    void AddNextVechicleToQueue();
    void CreatePrototypes( QWidget* parent = nullptr ) ;

private:
    IVechicleModel* GetCarPrototype( VechicleType id );
    void worker_thread();

    VechicleMap m_CarPrototypes;
    std::mutex m_CarQueueMtx;
    std::mutex m_CarPrototypeMtx;
    VechicleQueue m_VechiclesQueue;
    std::condition_variable cv;
    std::thread m_Thread;
    bool isRunning;

    static constexpr int FINAL_POINT = 500;
};

#endif // CVECHICLEMANAGER_H

