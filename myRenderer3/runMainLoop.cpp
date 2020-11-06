#include <crtdbg.h>
#include "engine.h"
#include "getKeyInput.h"
#include "frameRateController.h"
#include "windowHandler.h"
#include "profileManager.h"

void runMainLoop()
{
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

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

