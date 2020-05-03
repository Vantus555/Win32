// Lab1.cpp : Определяет точку входа для приложения.
//

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <random>
#include <time.h>
#include <tchar.h>
#include <stdlib.h>
#include "m_Window.h"

int WinWidth = 500;
int WinHeight = 500;
int Wx2 = 700;
int Wy2 = 100;

LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);

TCHAR Win2Name[] = _T("Main2Frame");
TCHAR Win2Title[] = _T("Окно 2");
MSG msg;

m_Window Win2;

int WINAPI _tWinMain(HINSTANCE This, HINSTANCE Prev, LPTSTR cmd, int mode) {
	Win2.WNDCLASSInit(This, Win2Name, WNDPROC(WndProc2));
	Win2.Register();
	Win2.m_CreateWindow(Win2Name, Win2Title, Wx2, Wy2, WinWidth, WinHeight, This);
	Win2.Show(mode);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_USER + 1:
	{
		PAINTSTRUCT ps;
		MessageBox(hWnd,
			_T("Дескриптор получен!"),
			_T("Сообщение"), MB_OK);
		HDC hdc = GetDC(hWnd); 
		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
		SelectObject(hdc, brush);
		
		DeleteObject(brush);
		EndPaint(hWnd, &ps);
	}

		break;
	case WM_USER + 2:
		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}