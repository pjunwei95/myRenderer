#pragma once
#include "engine.h"

class Timer 
{
public:
    typedef LARGE_INTEGER Clock;
    typedef LARGE_INTEGER& ClockHandle;

    Timer() : m_isStopped{ false }
    {
        start();
    }
    ~Timer() 
    {
        if (!m_isStopped)
            stop(); //stop timer
    }

    void start()
    {
        updateTimeStamp(m_StartTime); //start timer
    }

    //This function will stop the time and convert the stoptime to a readable time duration difference
    //in microseconds
    void stop()
    {
        updateTimeStamp(m_StopTime);
        m_StopTime.QuadPart = (m_StopTime.QuadPart - m_StartTime.QuadPart); //the units here are in seconds
        m_StopTime.QuadPart *= 1000000; //convert seconds to microseconds
        m_StopTime.QuadPart /= getSystemFrequency().QuadPart; //machine independence
        m_isStopped = true;
    }

    void updateTimeStamp(ClockHandle timer)
    {
        QueryPerformanceCounter(&timer);
    }

    float getDurationMs()
    {
        return (float)m_StopTime.QuadPart / 1000;
    }

    float getDurationSeconds()
    {
        return (float)m_StopTime.QuadPart / 1000000;
    }

    Clock getDurationUs() { return m_StopTime; }

private:
    bool m_isStopped;
    Clock m_StartTime;
    Clock m_StopTime;
};