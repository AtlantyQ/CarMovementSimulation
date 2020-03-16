#ifndef CVehicleMANAGER_H
#define CVehicleMANAGER_H

#include <QObject>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <vector>
#include <map>
#include "IVechicleManager.h"
#include "IVechicleInterface.h"

typedef std::vector<std::unique_ptr<IVehicleModel>> VehicleQueue;
typedef std::map< VehicleType, std::unique_ptr<IVehicleModel> > VehicleMap;

class CVehicleManager : public IVehicleManager
{
public:
    CVehicleManager();
    virtual ~CVehicleManager();
    void AddNextVehicleToQueue();
    void CreatePrototypes( QWidget* parent = nullptr ) ;

private:
    IVehicleModel* GetCarPrototype( VehicleType id );
    bool IsAboutToCrash(VehicleQueue::iterator Vehicle);
    void worker_thread();

    VehicleMap m_CarPrototypes;
    std::mutex m_CarQueueMtx;
    std::mutex m_CarPrototypeMtx;
    VehicleQueue m_VehiclesQueue;
    std::condition_variable cv;
    std::thread m_Thread;
    bool isRunning;

    static constexpr int FINAL_POINT = 750;
    static constexpr int MAX_DISTANCE = 80;
};

#endif // CVehicleMANAGER_H

