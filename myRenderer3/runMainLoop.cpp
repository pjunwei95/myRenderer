#include "engine.h"
#include "getKeyInput.h"
#include "frameRateController.h"
#include "windowHandler.h"
#include <crtdbg.h>
//#include "profiler.h"
#include "test.h"
#include "stopwatch.h"

void runMainLoop()
{
    // Enable run-time memory check for debug builds.
    //#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    //#endif

    //int * pi = new int;
    //pi;

    FrameRateController frc;

    WindowHandler wh;

    if(wh.createWindow())
    {

        while (!getIsDone())
        {

            Stopwatch frameWatch;
            wh.drawWindow();

            getKeyInput();

            wh.updateWindow();

            frc.idleUntilFPSLimit(frameWatch);

        }
        wh.destroyWindow();
    }

}

