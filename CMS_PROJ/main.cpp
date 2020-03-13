#include "CMainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);//Base Qt class, which is responsible for handling main loop of events

    CMainWindow w;
    w.show();

    return app.exec();//Starts main loop of events
}
