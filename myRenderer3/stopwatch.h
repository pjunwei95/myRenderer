#pragma once

class Stopwatch 
{
public:
    typedef LARGE_INTEGER Timer;
    typedef LARGE_INTEGER& TimerHandle;

    Stopwatch();
    ~Stopwatch();

    inline void updateTimeStamp(TimerHandle timer) { QueryPerformanceCounter(&timer); }
    inline void start() { updateTimeStamp(m_StartTime); } //start timer

    //This function will stop the time and convert the stoptime to a readable time duration difference
    //in microseconds
    void stop();
    float getDurationMs();
    float getDurationSeconds();
    Stopwatch::Timer getDurationUs();

private:
    bool m_isStopped;
    Timer m_StartTime;
    Timer m_StopTime;
};