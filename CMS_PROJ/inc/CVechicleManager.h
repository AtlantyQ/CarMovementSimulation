#ifndef CVehicleMANAGER_H
#define CVehicleMANAGER_H

#include <QObject>
#include <QTimer>
#include <mutex>
#include <vector>
#include <map>
#include "IVechicleManager.h"
#include "IVechicleInterface.h"

typedef std::vector<std::unique_ptr<IVehicleModel>> VehicleQueue;
typedef std::map< VehicleType, std::unique_ptr<IVehicleModel>> VehicleMap;

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
    VehicleQueue m_VehiclesQueue;
    std::mutex m_CarQueueMtx;
    QTimer m_AsyncCaller;


    static constexpr int FINAL_POINT = 750;
    static constexpr int MIN_ALLOWED_DISTANCE = 140;
    static constexpr int MAX_VEH_NUM = 5;
};

#endif // CVehicleMANAGER_H

