// Lab1.cpp : Определяет точку входа для приложения.
//

#include <random>
#include <time.h>
#include <tchar.h>
#include "m_Window.h"

int WinWidth = 500;
int WinHeight = 500;
int Wx1 = 100;
int Wy1 = 100;

LRESULT CALLBACK WndProc1(HWND, UINT, WPARAM, LPARAM);

TCHAR Win1Name[] = _T("Main1Frame");
TCHAR Win1Title[] = _T("Окно 1");
TCHAR Win2Name[] = _T("Main2Frame");
TCHAR Win2Title[] = _T("Окно 2");
MSG msg;

m_Window Win1;

int WINAPI _tWinMain(HINSTANCE This, HINSTANCE Prev, LPTSTR cmd, int mode) {
	Win1.WNDCLASSInit(This, Win1Name, WNDPROC(WndProc1));
	Win1.Register();
	Win1.m_CreateWindow(Win1Name, Win1Title, Wx1, Wy1, WinWidth, WinHeight, This);
	Win1.Show(mode);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HWND h = FindWindow(Win2Name, Win2Title);
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONUP:
		if (h) {
			int success = MessageBox(hWnd, _T("Окно 2 открыто!"), _T("Сообщение"), MB_OK);
			if (success) {
				SendMessage(h, WM_USER + 1, WPARAM(hWnd), 0);
				/*MessageBox(hWnd,
					_T("Сообщение передано в окно 2!"),
					_T("Сообщение"), MB_OK);*/
			}
		}
		else
			MessageBox(hWnd,
				_T("Окно 2 закрыто!"),
				_T("Сообщение"), MB_OK);
		break;
	case WM_RBUTTONUP:
		if (h) {
			SendMessage(h, WM_USER + 2, WPARAM(hWnd), 0);
			Sleep(5000);
			DestroyWindow(hWnd);
		}
		else
			MessageBox(hWnd,
				_T("Окно 2 закрыто!"),
				_T("Сообщение"), MB_OK);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}