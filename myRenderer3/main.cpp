#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <stdio.h>
#define FPS 30

BOOL isDone = FALSE;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void printKeyPressed(MSG &msg);

void runMessageLoop();

int main()
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	HINSTANCE hInstance = 0;
	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Learn to Program Windows",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, 1);

	// Run the message loop.

	runMessageLoop();

	return 0;
}

void runMessageLoop()
{
	MSG msg = {};
	LARGE_INTEGER nFrequency;
	QueryPerformanceFrequency(&nFrequency);
	while (!isDone)
	{
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		// get start
		LARGE_INTEGER nStartTime;

		// get elapsed time
		// 1s = 1 000 000 micro s = 30 frames
		// 1/30 = 1 frame
		// x < 1/30
		LARGE_INTEGER  frameTime;
		frameTime.QuadPart = 1000000 / FPS;

		QueryPerformanceCounter(&nStartTime);

		// start of keypress detection
		printKeyPressed(msg);

		TranslateMessage(&msg);
		DispatchMessage(&msg);

		while (1)
		{
			LARGE_INTEGER nStopTime;
			// get new elapsed time
			// if (new elapsed time - start
			QueryPerformanceCounter(&nStopTime);
			nStopTime.QuadPart = (nStopTime.QuadPart - nStartTime.QuadPart) * 1000000;
			nStopTime.QuadPart /= nFrequency.QuadPart;
			if (nStopTime.QuadPart > frameTime.QuadPart) {
				break;
			}
		}
		//printf("%f\n", (float) nElapsed.QuadPart / 1000);
	}
}

void printKeyPressed(MSG &msg)
{

	switch (msg.message)
	{
		case WM_KEYDOWN:
			switch (msg.wParam)
			{
				case VK_ESCAPE:
					isDone = TRUE;
					break;
			}
			printf("KEY PRESSED -> \"%c\" ASCII Value = %d\n", (char) msg.wParam, (int) msg.wParam);
			break;
	}
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;

		}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}