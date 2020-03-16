#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "IVechicleManager.h"

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow() = default;
    void show();

private:
    Q_SLOT void TimeOut();

    QWidget m_Road;
    QTimer m_Timer;
    IVehicleManager* m_VehicleCtrl;

    static constexpr int maxTimeout = 7500;
    static constexpr int minTimeout = 2000;

};
#endif // CMAINWINDOW_H
