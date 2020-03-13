#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <thread>
#include <mutex>
#include <queue>
#include <map>
#include "IVechicleInterface.h"

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

private:
    void CreateVechicle();
    IVechicleCtrl* getCarPrototype( VechicleType carType );

    Q_SLOT void sltTimeout();

    QWidget m_Road;
    QTimer m_Timer;
    std::queue< std::unique_ptr<IVechicleCtrl> > m_VechiclesQue;
    std::mutex m_CarCtrlMtx;
    std::mutex m_CarPrototypeMtx;

    std::map< VechicleType, std::unique_ptr<IVechicleCtrl> > m_CarPrototypes;

    static constexpr int maxTimeout = 5000;
    static constexpr int minTimeout = 1000;


};
#endif // CMAINWINDOW_H
