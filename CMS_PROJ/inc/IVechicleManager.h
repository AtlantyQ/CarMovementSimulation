#ifndef IVECHCICLEMANAGER_H
#define IVECHCICLEMANAGER_H

#include <QWidget>

class IVechicleManager
{
public:
    IVechicleManager() = default;
    virtual ~IVechicleManager() = default;
    virtual void AddNextVechicleToQueue() = 0;
    virtual void CreatePrototypes( QWidget* parent = nullptr) = 0;
};



#endif // IVECHCICLEMANAGER_H
