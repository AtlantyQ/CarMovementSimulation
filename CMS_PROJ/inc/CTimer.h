#ifndef CTIMER_H
#define CTIMER_H

#include <QTime>

class Timer : public QTime
{
public:
    Timer() : isRunning(false)
            , wasCheckedStart(false)
            , wasCheckedStop(false)
            , m_dtMv(0.f)
            , m_dtStop(0.f)
            , m_delta(0.f)

    {
    }
    ~Timer() = default;

    void start()
    {
        if(!isStarted())
        {
            QTime::start();
            isRunning = true;
        }
    }

    void SetStopPoint()
    {
        if(!wasCheckedStop)
        {
            m_dtStop = QTime::elapsed();
            wasCheckedStop = true;
            wasCheckedStart = false;
        }

    }

    void SetStartPoint()
    {
        if(!wasCheckedStart)
        {
            m_dtMv = QTime::elapsed();
            wasCheckedStop = false;
            wasCheckedStart = true;
        }
    }

    double GetStopPoint()
    {
        return m_dtStop;
    }

    double GetStartPoint()
    {
        return m_dtMv;
    }

    void SetDeltaTime( double delta )
    {
        m_delta = ( delta > 0 )? delta : 0;
    }

    double GetDelta()
    {
        return m_delta;
    }

    bool isStarted() { return isRunning; }

private:
    bool isRunning;
    bool wasCheckedStart;
    bool wasCheckedStop;
    double m_dtMv;
    double m_dtStop;
    double m_delta;
};

#endif // CTIMER_H
