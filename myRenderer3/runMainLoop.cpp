#include "getKeyInput.h"
#include "frameRateController.h"
#include "windowHandler.h"
#include "profileManager.h"
#include "render.h"

void RunMainLoop()
{
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

    FrameRateController frc;
    WindowHandler wh;

    while (!Engine::Instance().GetIsDone())
    {
        //TODO encapsulate framewatch to frc class
        Stopwatch frameWatch;
        {
            PROFILE_SCOPED(Frame);
            wh.drawWindow();
            getKeyInput();
            wh.updateWindow();
        }
        frc.idleUntilFPSLimit(frameWatch);
        ProfileManager::Instance().OnProfileFlip();
    }
}

