#pragma once
#include <Windows.h>

class Timer 
{
public:
    typedef LARGE_INTEGER Clock;
    typedef LARGE_INTEGER& ClockHandle;

    Timer() 
    {
        QueryPerformanceFrequency(&m_Frequency); //to be called only once. not per frame
        updateTimeStamp(m_StartTime); //start timer
    }
    ~Timer() 
    {
        stop(); //stop timer
    }

    //This function will stop the time and convert the stoptime to a readable time duration difference
    //in microseconds
    void stop()
    {
        updateTimeStamp(m_StopTime);
        m_StopTime.QuadPart = (m_StopTime.QuadPart - m_StartTime.QuadPart); //the units here are in seconds
        m_StopTime.QuadPart *= 1000000; //convert seconds to microseconds
        m_StopTime.QuadPart /= m_Frequency.QuadPart; //machine independence
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
    Clock m_Frequency;

    Clock m_StartTime;
    Clock m_StopTime;
};