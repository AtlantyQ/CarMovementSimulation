#ifndef CVehicleMANAGER_H
#define CVehicleMANAGER_H

#include <QObject>
#include <QTimer>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <vector>
#include <map>
#include <future>
#include "IVechicleManager.h"
#include "IVechicleInterface.h"

typedef std::vector<std::unique_ptr<IVehicleModel>> VehicleQueue;
typedef std::map< VehicleType, std::unique_ptr<IVehicleModel> > VehicleMap;

class CVehicleManager : public IVehicleManager
{
    Q_OBJECT

public:
    CVehicleManager();
    virtual ~CVehicleManager();
    void AddNextVehicleToQueue();
    void CreatePrototypes( QWidget* parent = nullptr ) ;

private:
    IVehicleModel* GetCarPrototype( VehicleType id );
    bool IsAboutToCrash(VehicleQueue::iterator currentVehicle );
    void worker();
private slots:
    void AsyncWorkerCaller();

private:
    VehicleMap m_CarPrototypes;
    std::mutex m_CarQueueMtx;
    std::mutex m_CarPrototypeMtx;
    VehicleQueue m_VehiclesQueue;
    QTimer m_AsyncCaller;


    static constexpr int FINAL_POINT = 750;
    static constexpr int MIN_ALLOWED_DISTANCE = 140;
    static constexpr int MAX_VEH_NUM = 5;
};

#endif // CVehicleMANAGER_H

