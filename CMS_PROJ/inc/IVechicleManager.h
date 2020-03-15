#ifndef IVECHCICLEMANAGER_H
#define IVECHCICLEMANAGER_H

#include "IVechicleInterface.h"

class IVechicleManager
{
public:
    IVechicleManager() = default;
    virtual ~IVechicleManager() = default;
    virtual void AddNextVechicleToQueue() = 0;
};



#endif // IVECHCICLEMANAGER_H
