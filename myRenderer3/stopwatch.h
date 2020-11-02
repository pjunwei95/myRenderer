#pragma once
#include "engine.h"
#include <assert.h>

class Stopwatch 
{
public:
    typedef LARGE_INTEGER Timer;
    typedef LARGE_INTEGER& TimerHandle;

    Stopwatch() : m_isStopped{ false }
    {
        start();
    }
    ~Stopwatch() 
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

    void updateTimeStamp(TimerHandle timer)
    {
        QueryPerformanceCounter(&timer);
    }

    float getDurationMs()
    {
        stop();
        return (float)m_StopTime.QuadPart / 1000;
    }

    float getDurationSeconds()
    {
        stop();
        return (float)m_StopTime.QuadPart / 1000000;
    }

    Timer getDurationUs() 
    { 
        stop();
        return m_StopTime;
    }

private:
    bool m_isStopped;
    Timer m_StartTime;
    Timer m_StopTime;
};