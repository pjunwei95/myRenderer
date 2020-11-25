#pragma once
#include "stopwatch.h"

class FrameRateController
{
public:
    FrameRateController();

    void idleUntilFPSLimit(Stopwatch& timer);

    bool isWithinFrameRate(Stopwatch& timer);

private:
    Stopwatch::Timer m_DefaultFrameTime;
};


