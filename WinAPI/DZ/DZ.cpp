// DZ.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "DZ.h"
#include <math.h>
#include <memory>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DZ, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DZ));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DZ));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DZ);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            HPEN b = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
            HPEN standart = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

            SelectObject(hdc, b);
            MoveToEx(hdc, 100, 0, NULL);
            LineTo(hdc, 100, 0);
            LineTo(hdc, 100, 1000);
            MoveToEx(hdc, 0, 400, NULL);
            LineTo(hdc, 0, 400);
            LineTo(hdc, 1000, 400);

            for (size_t i = 0; i <= 720; i+=40) {
                WCHAR* hah;
                if (i >= 10 && i < 100) {
                    hah = (WCHAR*)malloc(2);
                    wsprintf(hah, TEXT("%d"), i);
                    TextOut(hdc, 100 + i, 400, hah, 2);
                }
                else {
                    hah = (WCHAR*)malloc(3);
                    wsprintf(hah, TEXT("%d"), i);
                    TextOut(hdc, 100 + i, 400, hah, 3);
                }
            }
            /////////////////////////////////////////////////////////////////////
            for (size_t i = 40; i < 320; i += 40) {
                WCHAR* hah; 
                if (i >= 10 && i < 100) {
                    hah = (WCHAR*)malloc(3);
                    wsprintf(hah, TEXT("-%d"), i);
                    TextOut(hdc, 50, 400 + i, hah, 3);
                }
                else {
                    hah = (WCHAR*)malloc(4);
                    wsprintf(hah, TEXT("-%d"), i);
                    TextOut(hdc, 50, 400 + i, hah, 4);
                }
            }
            ////////////////////////////////////////////////////////////////
            int y = 360;
            for (size_t i = 40; i <= 400; i += 40) {
                WCHAR* hah;
                if (i >= 10 && i < 100) {
                    hah = (WCHAR*)malloc(2);
                    wsprintf(hah, TEXT("%d"), i);
                    TextOut(hdc, 50, y, hah, 2);
                }
                else {
                    hah = (WCHAR*)malloc(3);
                    wsprintf(hah, TEXT("%d"), i);
                    TextOut(hdc, 50, y, hah, 3);
                }
                y-=40;
            }

            DeleteObject(b);

            SelectObject(hdc, standart);

            for (int a = 1; a < 720; a++) {
                int y = pow((1 + 2*sin(15*a))*(1 + cos(35*a)), (1 + 5*cos(6*a))*(1 - sin(20*a)));
                LineTo(hdc, a+100, y+400);
            }
            for (int a = 1; a < 720; a++) {
                int y = pow((1 + 2*sin(15*a))*(1 + cos(35*a)), (1 + 5*cos(6*a))*(1 - sin(20*a)));
                LineTo(hdc, a+100, -y+400);
            }
            //LineTo(hdc, 720, 400);

            DeleteObject(standart);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
