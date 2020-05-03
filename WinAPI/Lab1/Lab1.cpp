// Lab1.cpp : Определяет точку входа для приложения.
//

#include <Windows.h>
#include <tchar.h>
#include <random>
#include <time.h>

int WinWidth = 300;
int WinHeight = 1000;
int x = 100;
int y = 100;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

int WINAPI _tWinMain(HINSTANCE This,
	HINSTANCE Prev,
	LPTSTR cmd,
	int mode)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wc;

	wc.hInstance = This;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);


	if (!RegisterClass(&wc)) return 0;

	hWnd = CreateWindow(WinName,
		_T("Форматирование диска!"),
		WS_OVERLAPPEDWINDOW,
		x,
		y,
		WinWidth,
		WinHeight,
		HWND_DESKTOP,
		NULL,
		This,
		NULL);

	ShowWindow(hWnd, mode);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	srand(time(0));
	int r = rand() % 8;
	int step = 1;
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_RBUTTONDOWN:
		MessageBox(hWnd, 
			_T("Функция перезагрузки копьютера ExitWindows(EWX_REBOOT, 0);"),
			_T("Перезагрузка"), MB_OK);
		//ExitWindows(EWX_REBOOT, 0);
		break;
	case WM_MOUSEMOVE:
		switch (r)
		{
		case 0:
			MoveWindow(hWnd, x += step, y, WinWidth, WinHeight, true);
			break;
		case 1:
			MoveWindow(hWnd, x, y += step, WinWidth, WinHeight, true);
			break;
		case 2:
			MoveWindow(hWnd, x -= step, y, WinWidth, WinHeight, true);
			break;
		case 3:
			MoveWindow(hWnd, x, y -= step, WinWidth, WinHeight, true);
			break;
		case 4:
			MoveWindow(hWnd, x += step, y += step, WinWidth, WinHeight, true);
			break;
		case 5:
			MoveWindow(hWnd, x -= step, y -= step, WinWidth, WinHeight, true);
			break;
		case 6:
			MoveWindow(hWnd, x += step, y -= step, WinWidth, WinHeight, true);
			break;
		case 7:
			MoveWindow(hWnd, x -= step, y += step, WinWidth, WinHeight, true);
			break;
		default:
			break;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

