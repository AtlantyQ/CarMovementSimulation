#include "CMainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);//Base Qt class, responsible for handling loop of events

    CMainWindow w;
    w.show();

    return app.exec();//Starts loop of events
}
