
#include <gtest/gtest.h>

#include <QApplication>

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
