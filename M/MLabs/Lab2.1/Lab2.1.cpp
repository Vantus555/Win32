#include <Windows.h>
#include <tchar.h>
#include <time.h>

int winWidth = 490;
int winHeight = 510;
int x = 100;
int y = 100;
unsigned int step = 100;

WNDCLASS wc;
int r = 255, g = 255, b = 255;

HBRUSH color_of_window = CreateSolidBrush(RGB(r, g, b));

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame"); // Имя 1-ого окна
TCHAR WinTitle[] = _T("Окно 1"); // Надпись 1-ого окна
TCHAR WinName2[] = _T("MainFrame2"); // Имя 2-ого окна
TCHAR WinTitle2[] = _T("Окно 2"); // Надпись 2-ого окна

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
	HWND h = FindWindow(WinName2, WinTitle2);
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break; case WM_LBUTTONUP:
		{
			if (h) {
				// Вывод сообщения
				int success = MessageBox(hWnd, _T("Окно 2 открыто!"), _T("Сообщение"), MB_OK);
				if (success) {
				// Отправка сообщения в другое окно
					SendMessage(h, WM_USER + 1, WPARAM(hWnd), 0);
				}
			}
			else
				MessageBox(hWnd,
					_T("Окно 2 закрыто!"),
					_T("Сообщение"), MB_OK);
			break;
		case WM_RBUTTONUP:
			if (h) {
				// Отправка сообщения в другое окно и закрытие первого окна
				SendMessage(h, WM_USER + 2, WPARAM(hWnd), 0);
				Sleep(5000);
				DestroyWindow(hWnd);
			}
			else
				MessageBox(hWnd,
					_T("Окно 2 закрыто!"),
					_T("Сообщение"), MB_OK);
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
