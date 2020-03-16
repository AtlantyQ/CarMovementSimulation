#ifndef IVECHCICLEMANAGER_H
#define IVECHCICLEMANAGER_H

#include <QWidget>

class IVehicleManager
{
public:
    IVehicleManager() = default;
    virtual ~IVehicleManager() = default;
    virtual void AddNextVehicleToQueue() = 0;
    virtual void CreatePrototypes( QWidget* parent = nullptr) = 0;
};



#endif // IVECHCICLEMANAGER_H
