#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <stdio.h>
#define FPS 30

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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

	MSG msg = { };
	LARGE_INTEGER nFrequency;
	QueryPerformanceFrequency(&nFrequency);
	while (PeekMessage(&msg, NULL, 0, 0, 0))
	{
		// get start
		LARGE_INTEGER nStartTime;
		
		
		
		

		// get elapsed time
		// 1s = 1 000 000 micro s = 30 frames
		// 1/30 = 1 frame
		// x < 1/30
		LARGE_INTEGER  frameTime;
		frameTime.QuadPart = 1000000 / FPS;

		
		QueryPerformanceCounter(&nStartTime);
		
		switch (msg.message)
		{
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_KEYDOWN:
			// 
			// Perform any required cleanup. 
			// 
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);

		while (1) 
		{
			LARGE_INTEGER nStopTime;
			LARGE_INTEGER nElapsed;
			// get new elapsed time
			// if (new elapsed time - start
			QueryPerformanceCounter(&nStopTime);
			nElapsed.QuadPart = (nStopTime.QuadPart - nStartTime.QuadPart) * 1000000;
			nElapsed.QuadPart /= nFrequency.QuadPart;
			if (nElapsed.QuadPart > frameTime.QuadPart) {
				break;
			}
		}
		//printf("%f\n", (float) nElapsed.QuadPart / 1000);

	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);



		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW +1));

		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}