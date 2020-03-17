QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    tools/googletest-release-1.8.1/googletest/src/gtest-all.cc \
    tools/googletest-release-1.8.1/googlemock/src/gmock-all.cc \
    tools/googletest-release-1.8.1/googlemock/src/gmock_main.cc \
    CMainWindow_test.cpp \
    main.cpp

HEADERS +=  tools/mocks/CVehicleManager_mock.h \


FORMS +=

INCLUDEPATH +=  tools/googletest-release-1.8.1/googletest/ \
                tools/googletest-release-1.8.1/googletest/include/ \
                tools/googletest-release-1.8.1/googletest/googlemock/ \
                tools/googletest-release-1.8.1/googlemock/include \
                ../../../CMS_PROJ/src \
                ../../../CMS_PROJ/inc \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
