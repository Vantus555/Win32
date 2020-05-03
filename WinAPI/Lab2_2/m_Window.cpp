#include "m_Window.h"

void m_Window::m_CreateWindow(const TCHAR* WinName, const TCHAR* WinTitle, int x, int y, int WinWidth, int WinHeight, HINSTANCE hINST, HWND Parent, int style)
{
	this->hWnd = CreateWindow(WinName,
		WinTitle,
		style,
		x,
		y,
		WinWidth,
		WinHeight,
		Parent,
		NULL,
		hINST,
		NULL);
}

void m_Window::WNDCLASSInit(HINSTANCE& hINST, const TCHAR* WinName, WNDPROC WndProc)
{
	wc.hInstance = hINST;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
}

bool m_Window::Register()
{
	if (!RegisterClass(&wc))
		return false;
	else return true;
}

void m_Window::Show(int mode)
{
	ShowWindow(hWnd, mode);
}
