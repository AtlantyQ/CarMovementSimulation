// Copyright © 2019 Aptiv. All rights reserved.
// Generation started on 2020-03-17 23:17:06.490497

#include <gmock/gmock.h>
#include  "CVechicleManager.h"

// Mock class definition
class CVehicleManagerMock : public IVehicleManager
{
public:
   virtual ~CVehicleManagerMock() {}
   MOCK_METHOD0( AddNextVehicleToQueue, void() );
   MOCK_METHOD1( CreatePrototypes, void(QWidget*) );
   MOCK_METHOD0( AsyncWorkerCaller, void() );
   MOCK_METHOD0( worker, void() );
   MOCK_METHOD1( GetCarPrototype, IVehicleModel*(VehicleType) );
   MOCK_METHOD1( IsAboutToCrash, bool(VehicleQueue::iterator) );
};

