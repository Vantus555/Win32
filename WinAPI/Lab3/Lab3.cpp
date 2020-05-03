// Lab1.cpp : Определяет точку входа для приложения.
//

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
TCHAR Win1Title[] = _T("Переводчик");
MSG msg;

m_Window Win1;
HWND Translate_Text_Result;
HWND Text;
HWND TranslateC_A;
HWND TranslateC_B;
HWND hBtn;
HWND Translate_Text;


int WINAPI _tWinMain(HINSTANCE This, HINSTANCE Prev, LPTSTR cmd, int mode)
{
	Win1.WNDCLASSInit(This, Win1Name, WNDPROC(WndProc1));
	Win1.Register();
	Win1.m_CreateWindow(Win1Name, Win1Title, Wx1, Wy1, WinWidth, WinHeight, This);

	HMENU TranslateA = CreateMenu();

	HMENU SubMenuA = CreatePopupMenu();
	HMENU SubMenuB = CreatePopupMenu();

	AppendMenu(SubMenuA, MF_STRING, 0, _T("Русский"));
	AppendMenu(SubMenuA, MF_STRING, 0, _T("Английский"));
	AppendMenu(SubMenuA, MF_STRING, 0, _T("Немецкий"));
	AppendMenu(TranslateA, MF_POPUP, (UINT)SubMenuA, _T("Перевести с"));

	AppendMenu(SubMenuB, MF_STRING, 0, _T("Русский"));
	AppendMenu(SubMenuB, MF_STRING, 0, _T("Английский"));
	AppendMenu(SubMenuB, MF_STRING, 0, _T("Немецкий"));
	AppendMenu(TranslateA, MF_POPUP, (UINT)SubMenuB, _T("Перевести на"));

	SetMenu(Win1.hWnd, TranslateA);
	
	TranslateC_A = CreateWindow(_T("combobox"), NULL, 
		WS_VISIBLE | WS_CHILD | CBS_HASSTRINGS | CBS_DROPDOWN, 
		10, 40, 150, 100, Win1.hWnd, 0, 0, NULL);

	SendMessage(TranslateC_A, CB_ADDSTRING, 0, (LPARAM)_T("Русский"));
	SendMessage(TranslateC_A, CB_ADDSTRING, 0, (LPARAM)_T("Английский"));
	SendMessage(TranslateC_A, CB_ADDSTRING, 0, (LPARAM)_T("Немецкий"));
	/////////////////////////////////////////////////////////////////////////////
	TranslateC_B = CreateWindow(_T("combobox"), NULL,
		WS_VISIBLE | WS_CHILD | CBS_HASSTRINGS | CBS_DROPDOWN,
		200, 40, 150, 100, Win1.hWnd, 0, 0, NULL);

	SendMessage(TranslateC_B, CB_ADDSTRING, 0, (LPARAM)_T("Русский"));
	SendMessage(TranslateC_B, CB_ADDSTRING, 0, (LPARAM)_T("Английский"));
	SendMessage(TranslateC_B, CB_ADDSTRING, 0, (LPARAM)_T("Немецкий"));
	////////////////////////////////////////////////////////////////////////////
	Translate_Text = CreateWindow(_T("edit"), NULL,
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		10, 80, 340, 100, Win1.hWnd, 0, 0, NULL);

	hBtn = CreateWindow(_T("button"), _T("Перевод"),
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		120, 200, 120, 30, Win1.hWnd, (HMENU)1, 0, NULL);

	Text = CreateWindow(_T("static"), _T("Результат:"),
		WS_VISIBLE | WS_CHILD,
		10, 250, 80, 20, Win1.hWnd, 0, 0, NULL);

	Translate_Text_Result = CreateWindow(_T("edit"), NULL,
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY,
		10, 280, 340, 100, Win1.hWnd, 0, 0, NULL);

	ShowWindow(hBtn, SW_SHOWNORMAL);

	Win1.Show(mode);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CHAR text1[255] = { 0 };
	CHAR text2[255] = { 0 };
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		if (wParam == 1) {
			GetWindowText(TranslateC_A, (LPWSTR)text1, 255);
			GetWindowText(TranslateC_B, (LPWSTR)text2, 255);
			if(strcmp(text1,text2) == 0)
				MessageBox(Win1.hWnd, (LPWSTR)text1, _T("Сообщение"), MB_OK);
			MessageBox(Win1.hWnd, (LPWSTR)text2, _T("Сообщение"), MB_OK);
		}
			
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

