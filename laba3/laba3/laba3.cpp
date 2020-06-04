// laba3.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "laba3.h"

#define MAX_LOADSTRING 100
HWND scrH, scrV;

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
RECT r;
RECT rct;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
bool bIsRDraw = false;
bool bIsLDraw = false;
POINT ptPrev = { 0 };
HPEN hRPen = CreatePen(PS_SOLID, 10, RGB(100,101,10));
HPEN hLPen = CreatePen(PS_SOLID, 5, RGB(14, 88, 55));
int nHorizontalDifference = 0;
int nVerticalDifference = 0;
int nVerticalPosition = 0;
int nHorizontalPosition = 0;
const int nHorizontal = 1000;
const int nVertical = 450;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


 //   WinExec("C:\\Windows\\system32\\notepad.exe", 1);
    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LABA3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LABA3));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LABA3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LABA3);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    static int s1Pos, s1Min, s1Max, s2Pos, s2Min, s2Max;
    static HWND s1Scroll, s2Scroll;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_CREATE: {
        break;
    }
    case WM_VSCROLL:
        switch (LOWORD(wParam))
        {
        case SB_LINEDOWN:
            if (nVerticalPosition < nVerticalDifference)
                nVerticalPosition += 3;
            break;
        case SB_LINEUP:
            if (nVerticalPosition > 0)
                nVerticalPosition -= 3;
            break;
        case SB_THUMBTRACK:
            nVerticalPosition = HIWORD(wParam);
            break;
        }
        rct;
        GetClientRect(hWnd, &rct);
        SetScrollPos(hWnd, SB_VERT, nVerticalPosition, TRUE);
        InvalidateRect(hWnd, &rct, FALSE);
        break;
    case WM_HSCROLL:
        switch (LOWORD(wParam))
        {
        case SB_LINEDOWN:
            if (nHorizontalPosition < nHorizontalDifference)
                nHorizontalPosition += 3;
            break;
        case SB_LINEUP:
            if (nHorizontalPosition > 0)
                nHorizontalPosition -= 3;
            break;
        case SB_THUMBTRACK:
            nHorizontalPosition = HIWORD(wParam);
        }
        rct;
        GetClientRect(hWnd, &rct);
        SetScrollPos(hWnd, SB_HORZ, nHorizontalPosition, TRUE);
        InvalidateRect(hWnd, &rct, FALSE);
        break;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
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
    case WM_LBUTTONDOWN:
        bIsLDraw = TRUE;
        ptPrev.x = LOWORD(lParam);
        ptPrev.y = HIWORD(lParam);
        break;
    case WM_LBUTTONUP:
        if (bIsLDraw)
        {
            HDC hdc = GetDC(hWnd);
            SelectObject(hdc, hLPen);
            MoveToEx(hdc, ptPrev.x, ptPrev.y, NULL);
            LineTo(hdc, LOWORD(lParam), HIWORD(lParam));
            ReleaseDC(hWnd, hdc);
            bIsLDraw = FALSE;
        }
        break;
    case WM_RBUTTONDOWN:
        bIsRDraw = TRUE;
        ptPrev.x = LOWORD(lParam);
        ptPrev.y = HIWORD(lParam);
        break;
    case WM_RBUTTONUP:
        if (bIsRDraw)
        {
            HDC hdc = GetDC(hWnd);
            SelectObject(hdc, hRPen);
            MoveToEx(hdc, ptPrev.x, ptPrev.y, NULL);
            LineTo(hdc, LOWORD(lParam), HIWORD(lParam));
            ReleaseDC(hWnd, hdc);
            bIsRDraw = FALSE;
        }
        break;
    case WM_MOUSEMOVE:
        if (bIsLDraw)
        {
            HDC hdc = GetDC(hWnd);
            SelectObject(hdc, hLPen);
            MoveToEx(hdc, ptPrev.x, ptPrev.y, NULL);
            LineTo(hdc, ptPrev.x = LOWORD(lParam), ptPrev.y = HIWORD(lParam));
            ReleaseDC(hWnd, hdc);
        }
        else if (bIsRDraw)
        {
            HDC hdc = GetDC(hWnd);
            SelectObject(hdc, hRPen);
            MoveToEx(hdc, ptPrev.x, ptPrev.y, NULL);
            LineTo(hdc, ptPrev.x = LOWORD(lParam), ptPrev.y = HIWORD(lParam));
            ReleaseDC(hWnd, hdc);
        }
        break;
    case WM_PAINT:
        {
        GetClientRect(hWnd, &rct);
            PAINTSTRUCT ps;
            RECT rect;
            HBRUSH hBrush;
            HPEN hPen;
            POINT poly[4];
            BYTE polytype[4];
            HDC hdcBitmap;
            HBITMAP hBitmap, Bitmap; BITMAP bp;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            rect.left = 50 - nHorizontalPosition; rect.top = 50 - nVerticalPosition;
            rect.right = 100 - nHorizontalPosition; rect.bottom = 100 - nVerticalPosition;
            FillRect(hdc, &rect, (HBRUSH)CreateSolidBrush(RGB(255, 0, 0)));

            hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
            SelectObject(hdc, hPen);
            Ellipse(hdc, 150 - nHorizontalPosition, 50 - nVerticalPosition, 200 - nHorizontalPosition, 100 - nVerticalPosition);
            hBrush = CreateSolidBrush(RGB(0, 255, 0));
            SelectObject(hdc, hBrush);
            FloodFill(hdc, 175 - nHorizontalPosition, 75 - nVerticalPosition, RGB(0, 0, 255));

            MoveToEx(hdc, 300 - nHorizontalPosition, 100 - nVerticalPosition, NULL);
            poly[0].x = 300 - nHorizontalPosition;
            poly[0].y = 100 - nVerticalPosition;
            poly[1].x = 350 - nHorizontalPosition;
            poly[1].y = 50 - nVerticalPosition;
            poly[2].x = 400 - nHorizontalPosition;
            poly[2].y = 100 - nVerticalPosition;
            poly[3].x = 300 - nHorizontalPosition;
            poly[3].y = 100 - nVerticalPosition;
            polytype[0] = PT_LINETO; polytype[1] = PT_LINETO; polytype[2] = PT_LINETO; polytype[3] = PT_LINETO;
            hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
            SelectObject(hdc, hPen);
            PolyDraw(hdc, poly, polytype, 4);
            hBrush = CreateSolidBrush(RGB(100, 100, 100));
            SelectObject(hdc, hBrush);
            FloodFill(hdc, 350 - nHorizontalPosition, 75 - nVerticalPosition, RGB(0, 0, 255));

            rect.left = 500-nHorizontalPosition; rect.top = 100 - nVerticalPosition;
            rect.right = 550-nHorizontalPosition; rect.bottom = 50 - nVerticalPosition;
            FillRect(hdc, &rect, (HBRUSH)CreateSolidBrush(RGB(255, 0, 0)));
            hPen = CreatePen(PS_SOLID, 3, RGB(0, 200, 167));
            SelectObject(hdc, hPen);
            MoveToEx(hdc, 500 - nHorizontalPosition, 100 - nVerticalPosition, NULL);
            LineTo(hdc, 500 - nHorizontalPosition, 50 - nVerticalPosition);
            hPen = CreatePen(PS_SOLID, 4, RGB(0, 255, 47));
            SelectObject(hdc, hPen);
            LineTo(hdc, 550 - nHorizontalPosition, 50 - nVerticalPosition);
            hPen = CreatePen(PS_SOLID, 10, RGB(14, 61, 8));
            SelectObject(hdc, hPen);
            LineTo(hdc, 550 - nHorizontalPosition, 100 - nVerticalPosition);
            hPen = CreatePen(PS_SOLID, 15, RGB(14, 88, 167));
            SelectObject(hdc, hPen);
            LineTo(hdc, 500 - nHorizontalPosition, 100 - nVerticalPosition);

            hBitmap = LoadBitmap(GetModuleHandle(NULL),
                MAKEINTRESOURCE(ID_Img1));
            hdcBitmap = CreateCompatibleDC(hdc);
            SelectObject(hdcBitmap, hBitmap);
            GetObject(hBitmap, sizeof(bp), &bp);
            GetClientRect(hWnd, &r);
            StretchBlt(hdc, 50, 150,
                100, 80, hdcBitmap, 0,
                0, bp.bmWidth, bp.bmHeight, SRCCOPY);
            DeleteDC(hdcBitmap);
          
            hBitmap = LoadBitmap(GetModuleHandle(NULL),
                MAKEINTRESOURCE(ID_Img1));
            hdcBitmap = CreateCompatibleDC(hdc);
            HBITMAP hOldBM= (HBITMAP)SelectObject(hdcBitmap, hBitmap);
            GetObject(hBitmap, sizeof(bp), &bp);
            GetClientRect(hWnd, &r);
            SelectObject(hdc, hOldBM);
            BitBlt(hdc, 0, 0, r.right, r.bottom, hdcBitmap, -200+nHorizontalPosition,
                -150+nVerticalPosition, SRCCOPY);
            DeleteDC(hdcBitmap);

            if ((nHorizontalDifference = (nHorizontal - r.right)) > 0)
                SetScrollRange(hWnd, SB_HORZ, 0, nHorizontalDifference, TRUE);
            else
                SetScrollRange(hWnd, SB_HORZ, 0, 0, TRUE);
            if ((nVerticalDifference = (nVertical - r.bottom)) > 0)
                SetScrollRange(hWnd, SB_VERT, 0, nVerticalDifference, TRUE);
            else
                SetScrollRange(hWnd, SB_VERT, 0, 0, TRUE);
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
