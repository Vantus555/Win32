#pragma once
#include <Windows.h>
#include <tchar.h>

class m_Window
{
public:
	HWND hWnd;
	WNDCLASS wc;

	m_Window() {}
	void m_CreateWindow(const TCHAR* WinName,
		const TCHAR* WinTitle,
		int x,
		int y,
		int WinWidth,
		int WinHeight,
		HINSTANCE hINST);
	void WNDCLASSInit(HINSTANCE& hINST,
		const TCHAR* WinName,
		WNDPROC WndProc);
	bool Register();
	void Show(int mode);
};

