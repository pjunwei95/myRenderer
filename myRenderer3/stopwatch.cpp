#include "stopwatch.h"

Stopwatch::Stopwatch()
    : m_isStopped{ false }
{
    start();
}

Stopwatch::~Stopwatch()
{
    if (!m_isStopped)
        stop(); //stop timer
}

//This function will stop the time and convert the stoptime to a readable time duration difference
//in microseconds
void Stopwatch::stop()
{
    updateTimeStamp(m_StopTime);
    m_StopTime.QuadPart = (m_StopTime.QuadPart - m_StartTime.QuadPart); //the units here are in seconds
    m_StopTime.QuadPart *= 1000000; //convert seconds to microseconds
    //m_StopTime.QuadPart /= getSystemFrequency().QuadPart; //machine independence
    m_StopTime.QuadPart /= Engine::Instance().GetSystemFrequency().QuadPart; //machine independence
    m_isStopped = true;
}

float Stopwatch::getDurationMs()
{
    stop();
    return (float)m_StopTime.QuadPart / 1000;
}

float Stopwatch::getDurationSeconds()
{
    stop();
    return (float)m_StopTime.QuadPart / 1000000;
}

Stopwatch::Timer Stopwatch::getDurationUs()
{
    stop();
    return m_StopTime;
}