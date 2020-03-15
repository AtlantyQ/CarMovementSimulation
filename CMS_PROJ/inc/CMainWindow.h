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
    ~CMainWindow();

private:
    Q_SLOT void sltTimeOut();

    QWidget m_Road;
    QTimer m_Timer;
    IVechicleManager* m_VechicleCtrl;

    static constexpr int maxTimeout = 5000;
    static constexpr int minTimeout = 1000;

};
#endif // CMAINWINDOW_H
