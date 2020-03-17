#include "gtest/gtest.h"
#include "CMainWindow.h"
#include "tools/mocks/CVehicleManager_mock.h"
#include <iostream>
#include <stdio.h>

namespace
{
    CVehicleManagerMock* pCVehicleManagerMock;
}

class CMainWindowTesting : public ::testing::Test, public CMainWindow {
   public:

   CMainWindowTesting() {}
   virtual ~CMainWindowTesting() {}


   virtual void SetUp()
   {
       this->m_VehicleCtrl = &cvmMock;
   }
   virtual void TearDown()
   {
   }

   ::testing::StrictMock<CVehicleManagerMock> cvmMock;
};

TEST_F(CMainWindowTesting, CMainWindowTesting_show)
{

}

TEST_F(CMainWindowTesting, CMainWindowTesting_TimeOut)
{

}
