// Lab1.cpp : Определяет точку входа для приложения.
//

#include <process.h>
#include <iostream>
#include <random>
#include <time.h>
#include <tchar.h>
#include <string.h>
#include "m_Window.h"

int WinWidth = 500;
int WinHeight = 500;
int Wx1 = 100;
int Wy1 = 100;

LRESULT CALLBACK WndProc1(HWND, UINT, WPARAM, LPARAM);

TCHAR Win1Name[] = _T("Main1Frame");
TCHAR Win1Title[] = _T("Потоки");
MSG msg;

CRITICAL_SECTION flag;
HANDLE thread_1;
HANDLE thread_2;
m_Window Win1;
PAINTSTRUCT ps;
HDC hdc; 

bool b = true;

int WINAPI _tWinMain(HINSTANCE This, HINSTANCE Prev, LPTSTR cmd, int mode)
{
	Win1.WNDCLASSInit(This, Win1Name, WNDPROC(WndProc1));
	Win1.Register();
	Win1.m_CreateWindow(Win1Name, Win1Title, Wx1, Wy1, WinWidth, WinHeight, This);

	InitializeCriticalSection(&flag);
	Win1.Show(mode);


	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

DWORD WINAPI thread1(LPVOID t)
{
	srand(time(0));
	EnterCriticalSection(&flag);

	HDC h = GetDC(Win1.hWnd);
	HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
	SelectObject(h, brush);


	int r = rand() % 2;
	if (r == 0) 
		Pie(h, 10, 10, 470, 200, 240, 200, 240, 10);
	else
		Pie(h, 10, 10, 470, 200, 240, 10, 240, 200);

	DeleteObject(brush);

	LeaveCriticalSection(&flag);
	TerminateThread(thread_1, NULL);

	return 0;
}

DWORD WINAPI thread2(LPVOID t)
{

	srand(time(0));

	EnterCriticalSection(&flag);
	HDC h = GetDC(Win1.hWnd);

	TextOut(h, 10, 300, _T("Hello"), 6);

	//DeleteObject(hPen);
	LeaveCriticalSection(&flag);
	
	TerminateThread(thread_2, NULL);

	return 0;
}

LRESULT CALLBACK WndProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 20, NULL);
		break;
	case WM_TIMER:
		thread_1 = CreateThread(NULL, 0, &thread1, NULL, 0, NULL);
		thread_2 = CreateThread(NULL, 0, &thread2, NULL, 0, NULL);
		InvalidateRect(Win1.hWnd, 0, true);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteCriticalSection(&flag);
		PostQuitMessage(0);
		break; 
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


