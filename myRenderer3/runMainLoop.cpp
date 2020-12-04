#include "getKeyInput.h"
#include "frameRateController.h"
#include "profileManager.h"
#include "renderer.h"

void RunMainLoop()
{
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

    FrameRateController frc;
    Renderer renderer;

    while (!Engine::Instance().GetIsDone())
    {
        //TODO encapsulate frame watch to frc class
        Stopwatch frameWatch;
        {
            PROFILE_SCOPED(Frame);
            renderer.Clear();
            renderer.DrawTriangle();
            getKeyInput();
            renderer.SwapBuffer();
        }
        frc.idleUntilFPSLimit(frameWatch);
        ProfileManager::Instance().OnProfileFlip();
    }
}

