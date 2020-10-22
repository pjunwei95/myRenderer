#pragma once
#include "stopwatch.h"
#include "engine.h"
#include "logger.h"

class FrameRateController
{
public:
    FrameRateController();

    void idleUntilFPSLimit(Stopwatch timer);

    bool isWithinFrameRate(Stopwatch timer);

private:
    Stopwatch::Timer m_DefaultFrameTime;
};


