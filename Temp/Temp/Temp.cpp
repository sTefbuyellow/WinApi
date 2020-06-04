
#include "framework.h"
#include "Temp.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                HandleCreateMessage(HWND, RECT*, HBITMAP, BITMAP*, int, int);
void                HandleSizeMessage(HWND, RECT*, BITMAP*, int*, int*, int*, int*);
void                MoveCoordinates(int*, int*, int);
void                DoScrolling(HWND, RECT*, int, WPARAM, LONG, LONG, int*, int*);

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
    LoadStringW(hInstance, IDC_TEMP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEMP));

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

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEMP));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TEMP);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

    HWND hWnd = CreateWindowW(szWindowClass, szTitle,
        WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
        CW_USEDEFAULT, 0, 500, 320, nullptr, nullptr, hInstance, nullptr);

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
    static int bitmapX = 100, bitmapY = 100;
    static int vScrollPos = 0, hScrollPos = 0;
    static HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, L"image.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    static BITMAP bitmapInfo;
    static RECT rect;

    switch (message)
    {
    case WM_CREATE:
        HandleCreateMessage(hWnd, &rect, hBitmap, &bitmapInfo, bitmapX, bitmapY);
        break;
    case WM_SIZE:
        HandleSizeMessage(hWnd, &rect, &bitmapInfo, &bitmapX, &bitmapY, &hScrollPos, &vScrollPos);
        break;
    case WM_HSCROLL:
        DoScrolling(hWnd, &rect, SB_HORZ, wParam, rect.right, bitmapInfo.bmWidth, &bitmapX, &hScrollPos);
        break;
    case WM_VSCROLL:
        DoScrolling(hWnd, &rect, SB_VERT, wParam, rect.bottom, bitmapInfo.bmHeight, &bitmapY, &vScrollPos);
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
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        static HDC hCompatibleDC = CreateCompatibleDC(hdc);
        SelectObject(hCompatibleDC, hBitmap);
        BitBlt(hdc, bitmapX+50, bitmapY+50, bitmapInfo.bmWidth - bitmapX+50,
            bitmapInfo.bmHeight - bitmapY+50, hCompatibleDC, 0, 0, SRCCOPY);
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

void HandleCreateMessage(HWND hWnd,
    RECT* rect,
    HBITMAP hBitmap,
    BITMAP* bitmapInfo,
    int x,
    int y) {
    GetClientRect(hWnd, rect);
    GetObject(hBitmap, sizeof(BITMAP), bitmapInfo);
    SetScrollRange(hWnd, SB_HORZ, 0, bitmapInfo->bmWidth - rect->right, TRUE);
    SetScrollRange(hWnd, SB_VERT, 0, bitmapInfo->bmHeight - rect->bottom, FALSE);
    SetScrollPos(hWnd, SB_HORZ, x, TRUE);
    SetScrollPos(hWnd, SB_VERT, y, TRUE);
    EnableScrollBar(hWnd, SB_HORZ, ESB_DISABLE_LEFT);
    EnableScrollBar(hWnd, SB_VERT, ESB_DISABLE_UP);
}

void HandleSizeMessage(HWND hWnd,
    RECT* rect,
    BITMAP* bitmapInfo,
    int* x,
    int* y,
    int* hScrollPos,
    int* vScrollPos) {
    GetClientRect(hWnd, rect);
    SetScrollRange(hWnd, SB_HORZ, 0, (bitmapInfo->bmWidth - rect->right), TRUE);
    SetScrollRange(hWnd, SB_VERT, 0, (bitmapInfo->bmHeight - rect->bottom), FALSE);

    if (*x < rect->right - bitmapInfo->bmWidth) {
        *x = rect->right - bitmapInfo->bmWidth;
        *hScrollPos = bitmapInfo->bmWidth - rect->right;
        SetScrollPos(hWnd, SB_HORZ, *hScrollPos, TRUE);
    }
    if (*y < rect->bottom - bitmapInfo->bmHeight) {
        *y = rect->bottom - bitmapInfo->bmHeight;
        *vScrollPos = bitmapInfo->bmHeight - rect->bottom;
        SetScrollPos(hWnd, SB_VERT, *vScrollPos, TRUE);
    }
}

void MoveCoordinates(int* coord1, int* coord2, int delta) {
    *coord1 += delta;
    *coord2 -= delta;
}


void DoScrolling(HWND hWnd,
    RECT* rect,
    int type,
    WPARAM wParam,
    LONG rectBorder,
    LONG bitmapSize,
    int* coord,
    int* scrollCoord) {
    switch (LOWORD(wParam))
    {
    case SB_PAGEUP:
        MoveCoordinates(coord, scrollCoord, 60);
        break;
    case SB_PAGEDOWN:
        MoveCoordinates(coord, scrollCoord, -60);
        break;
    case SB_LINEUP:
        MoveCoordinates(coord, scrollCoord, 10);
        break;
    case SB_LINEDOWN:
        MoveCoordinates(coord, scrollCoord, -10);
        break;
    case SB_THUMBTRACK:
        *coord = -HIWORD(wParam);
        *scrollCoord = HIWORD(wParam);
        break;
    }
  

    SetScrollPos(hWnd, type, *scrollCoord, TRUE);
    InvalidateRect(hWnd, rect, FALSE);
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
