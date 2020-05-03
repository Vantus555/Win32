#include <Windows.h>
#include <tchar.h>
#include <time.h>

int winWidth = 490;
int winHeight = 510;
int x = 100;
int y = 100;
unsigned int step = 100;

WNDCLASS wc; 
int r = 0, g = 191, b = 255;

HBRUSH color_of_window = CreateSolidBrush(RGB(r, g, b));

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

int WINAPI _tWinMain(HINSTANCE This,
	HINSTANCE Prev, 	
	LPTSTR cmd, 		
	int mode) 		
{
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
		_T("Windows"), 	
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
	switch (message)
	{
	case WM_PAINT:
	{
		HDC hdc;
		HBRUSH brush;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		brush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, brush);
		//Pie(hdc, 10, 10, 470, 200, 240, 10, 240, 200);
		//Rectangle(hdc, 200, , (winWidth / 2) - 30, (winHeight / 2) - 10);
		Rectangle(hdc, (winWidth / 2) - step, (winHeight / 2) - step, (winWidth / 2) + step, (winHeight / 2) + step);
		EndPaint(hWnd, &ps);
	}
		break;
	case WM_LBUTTONUP:
		step += 10;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_RBUTTONUP:
		srand(time(NULL));
		r = rand() % 255;
		g = rand() % 255;
		b = rand() % 255;

		SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(r, g, b)));
		InvalidateRect(hWnd, NULL, TRUE);
		//MessageBox(hWnd, "������ ����������!", "�������", 0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
