#include <Windows.h>
#include <tchar.h>
#include <time.h>

int winWidth = 490;
int winHeight = 510;
int x = 500;
int y = 100;
unsigned int step = 100;

WNDCLASS wc;
int r = 255, g = 255, b = 255;

HBRUSH color_of_window = CreateSolidBrush(RGB(r, g, b));

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame2");
TCHAR WinTitle[] = _T("Окно 2");

int WINAPI _tWinMain(HINSTANCE This,
	HINSTANCE Prev,
	LPTSTR cmd,
	int mode) {
	HWND hWnd;
	MSG msg;

	wc.hInstance = This;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = color_of_window;

	if (!RegisterClass(&wc)) return 0;

	hWnd = CreateWindow(WinName,
		WinTitle,
		WS_OVERLAPPEDWINDOW,
		x,
		y,
		winWidth,
		winHeight,
		HWND_DESKTOP,
		NULL,
		This,
		NULL);

	ShowWindow(hWnd, mode);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	
	switch (message) {
	case WM_TIMER:
	{
		// Изменения цвета окно по таймеры
		RECT rc;
		HDC hdc = GetDC(hWnd);
		GetClientRect(hWnd, &rc);
		SetDCBrushColor(hdc, RGB(139, 0, 255));
		FillRect(hdc, &rc, (HBRUSH)GetStockObject(DC_BRUSH));
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;	
	case WM_USER + 1:
	{
		MessageBox(hWnd,
			_T("Дескриптор получен!\n"),
			_T("Сообщение"), MB_OK);
		HDC hdc = GetDC(hWnd);
		HBRUSH brush = CreateSolidBrush(RGB(255, 255, 0));
		SelectObject(hdc, brush);
		WCHAR dec[25];
		wsprintf(dec, TEXT("Дескриптор окна: %d"), wParam);
		TextOut(hdc, 10, 10, dec, 25);
		DeleteObject(brush);
	}
		break;
	case WM_USER + 2:
		// Установка таймера
		SetTimer(hWnd, 1, 1000, NULL);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
