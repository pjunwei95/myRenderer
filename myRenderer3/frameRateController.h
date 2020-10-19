#pragma once
#include "timer.h"
#include "engine.h"
#include "logger.h"

class FrameRateController
{
public:
    FrameRateController();

    void idleUntilFPSLimit(Timer timer);

    bool isWithinFrameRate(Timer timer);

private:
    Timer::Clock m_DefaultFrameTime;
};


