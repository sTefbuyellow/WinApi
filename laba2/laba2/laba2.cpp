// laba2.cpp : Определяет точку входа для приложения.
//
#include "framework.h"
#include "laba2.h"

#define MAX_LOADSTRING 100

const int IDM_Exit = 1;
const int IDM_Background_Img1 = 2;
const int IDM_Background_Img2 = 3;
const int IDM_Background_Img3 = 4;

const int IDM_Background_Red = 5;
const int IDM_Background_Green = 6;
const int IDM_Background_Blue = 7;


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
COLORREF bkgndcolor =NULL;
HMENU hMenu, hMenuFile, hMenuBackground, hMenuBackgroundImg, hMenuBackgroundColor;
HMENU hPMenu, hPMenuFile, hPMenuBackground, hPMenuBackgroundImg, hPMenuBackgroundColor;
HBITMAP hBitmap;
UINT imgCheck=IDM_Background_Img3, colorCheck=NULL;
int image = ID_Background_Img3;

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
    LoadStringW(hInstance, IDC_LABA2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LABA2));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LABA2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreatePatternBrush(LoadBitmap(hInstance, MAKEINTRESOURCE(image)));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LABA2);
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

//HMENU AppendMenu(( hFileMenu = CreatePopupMenu()), MF_ENABLED, MF_STRING
//    , IDM_Enable_Disable, "&Enable exit"

void ChangeImg(HWND hWnd, int choiceImg, UINT choice)
{
    colorCheck = NULL;
    imgCheck = choice;
    image = choiceImg;
    CheckMenuRadioItem(hMenuBackgroundImg, IDM_Background_Img1, IDM_Background_Img3, choice, MF_BYCOMMAND);
    CheckMenuRadioItem(hMenuBackgroundColor, IDM_Background_Red, IDM_Background_Blue, choice, MF_DISABLED);
    InvalidateRect(hWnd, NULL, TRUE);
    UpdateWindow(hWnd);
}

void ChangeBk(UINT choice, COLORREF color)
{
    colorCheck = choice;
    imgCheck = NULL;
    image = NULL;
    bkgndcolor = color;
    CheckMenuRadioItem(hMenuBackgroundColor, IDM_Background_Red, IDM_Background_Blue, choice, MF_BYCOMMAND);
    CheckMenuRadioItem(hMenuBackgroundImg, IDM_Background_Img1, IDM_Background_Img3, choice, MF_DISABLED);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HBRUSH greenBrush;
    switch (message)
    {
    case WM_CREATE:
    {
    
        HBITMAP hBm1 = LoadBitmap(hInst, MAKEINTRESOURCE(ID_Background_Img1_ICO));
        HBITMAP hBm2 = LoadBitmap(hInst, MAKEINTRESOURCE(ID_Background_Img2_ICO));
        HBITMAP hBm3 = LoadBitmap(hInst, MAKEINTRESOURCE(ID_Background_Img3_ICO));
        HBITMAP point = LoadBitmap(hInst, MAKEINTRESOURCE(ID_PointCheck));

        hMenu = CreateMenu();
        hMenuFile = CreatePopupMenu();
        hMenuBackground = CreatePopupMenu();
        hMenuBackgroundImg = CreatePopupMenu();
        hMenuBackgroundColor = CreatePopupMenu();
        AppendMenu(hMenu, MF_ENABLED | MF_POPUP, (UINT)hMenuFile, L"&File");
        AppendMenu(hMenu, MF_ENABLED | MF_POPUP, (UINT)hMenuBackground, L"&Background");
        AppendMenu(hMenu, MF_ENABLED | MF_POPUP, IDM_ABOUT, L"About");
        AppendMenu(hMenuFile, MF_ENABLED | MF_POPUP, IDM_Exit, L"&Exit");
        AppendMenu(hMenuBackground, MF_ENABLED | MF_POPUP, (UINT)hMenuBackgroundImg, L"&Image");
        AppendMenu(hMenuBackground, MF_ENABLED | MF_POPUP, (UINT)hMenuBackgroundColor, L"&Color");
        AppendMenu(hMenuBackgroundImg, MF_ENABLED | MF_POPUP | MF_BITMAP | MF_BYCOMMAND, IDM_Background_Img1, (LPWSTR)hBm1);
        AppendMenu(hMenuBackgroundImg, MF_ENABLED | MF_POPUP | MF_BITMAP | MF_BYCOMMAND, IDM_Background_Img2, (LPWSTR)hBm2);
        AppendMenu(hMenuBackgroundImg, MF_ENABLED | MF_POPUP | MF_BITMAP | MF_BYCOMMAND, IDM_Background_Img3, (LPWSTR)hBm3);
        CheckMenuRadioItem(hMenuBackgroundImg, IDM_Background_Img1, IDM_Background_Img3, IDM_Background_Img3, MF_BYCOMMAND);
        
        SetMenuItemBitmaps(hMenuBackgroundImg, 2, MF_BYCOMMAND, NULL, point);
        SetMenuItemBitmaps(hMenuBackgroundImg, 3, MF_BYCOMMAND, NULL, point);
        SetMenuItemBitmaps(hMenuBackgroundImg, 4, MF_BYCOMMAND, NULL, point);

        AppendMenu(hMenuBackgroundColor, MF_ENABLED | MF_POPUP, IDM_Background_Red, L"&Red");
        AppendMenu(hMenuBackgroundColor, MF_ENABLED | MF_POPUP, IDM_Background_Green, L"&Green");
        AppendMenu(hMenuBackgroundColor, MF_ENABLED | MF_POPUP, IDM_Background_Blue, L"&Blue");
        SetMenu(hWnd, hMenu);

       
  
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_Exit:
                DestroyWindow(hWnd);
                break;
            case IDM_Background_Blue:
                ChangeBk(IDM_Background_Blue, RGB(0, 0, 255));
                break;
            case IDM_Background_Green:
                ChangeBk(IDM_Background_Green,RGB(0, 255, 0));
                break;
            case IDM_Background_Red:
                ChangeBk(IDM_Background_Red, RGB(255, 0, 0));
                break;
            case IDM_Background_Img1:
                ChangeImg(hWnd, ID_Background_Img1, IDM_Background_Img1);
                break;
            case IDM_Background_Img2:
                ChangeImg(hWnd, ID_Background_Img2, IDM_Background_Img2);
                break;
            case IDM_Background_Img3:
                ChangeImg(hWnd, ID_Background_Img3, IDM_Background_Img3);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_CONTEXTMENU:
    {
        HBITMAP hBm1 = LoadBitmap(hInst, MAKEINTRESOURCE(ID_Background_Img1_ICO));
        HBITMAP hBm2 = LoadBitmap(hInst, MAKEINTRESOURCE(ID_Background_Img2_ICO));
        HBITMAP hBm3 = LoadBitmap(hInst, MAKEINTRESOURCE(ID_Background_Img3_ICO));
        HBITMAP point = LoadBitmap(hInst, MAKEINTRESOURCE(ID_PointCheck));

        hPMenu = CreatePopupMenu();

        hPMenuFile = CreatePopupMenu();
        hPMenuBackground = CreatePopupMenu();
        hPMenuBackgroundImg = CreatePopupMenu();
        hPMenuBackgroundColor = CreatePopupMenu();
        AppendMenu(hPMenu, MF_ENABLED | MF_POPUP, (UINT)hPMenuFile, L"&File");
        AppendMenu(hPMenu, MF_ENABLED | MF_POPUP, (UINT)hPMenuBackground, L"&Background");
        AppendMenu(hPMenu, MF_ENABLED | MF_POPUP, IDM_ABOUT, L"About");
        AppendMenu(hPMenuFile, MF_ENABLED | MF_POPUP, IDM_Exit, L"&Exit");
        AppendMenu(hPMenuBackground, MF_ENABLED | MF_POPUP, (UINT)hPMenuBackgroundImg, L"&Image");
        AppendMenu(hPMenuBackground, MF_ENABLED | MF_POPUP, (UINT)hPMenuBackgroundColor, L"&Color");
        AppendMenu(hPMenuBackgroundImg, MF_BITMAP, IDM_Background_Img1, (LPWSTR)hBm1);
        AppendMenu(hPMenuBackgroundImg, MF_ENABLED | MF_POPUP | MF_BITMAP, IDM_Background_Img2, (LPWSTR)hBm2);
        AppendMenu(hPMenuBackgroundImg, MF_ENABLED | MF_POPUP | MF_BITMAP | MF_BYCOMMAND, IDM_Background_Img3, (LPWSTR)hBm3);

        AppendMenu(hPMenuBackgroundColor, MF_ENABLED | MF_POPUP, IDM_Background_Red, L"&Red");
        AppendMenu(hPMenuBackgroundColor, MF_ENABLED | MF_POPUP, IDM_Background_Green, L"&Green");
        AppendMenu(hPMenuBackgroundColor, MF_ENABLED | MF_POPUP, IDM_Background_Blue, L"&Blue");

        SetMenuItemBitmaps(hPMenuBackgroundImg, 2, MF_BYCOMMAND, NULL, point);
        SetMenuItemBitmaps(hPMenuBackgroundImg, 3, MF_BYCOMMAND, NULL, point);
        SetMenuItemBitmaps(hPMenuBackgroundImg, 4, MF_BYCOMMAND, NULL, point);

        CheckMenuRadioItem(hPMenuBackgroundColor, IDM_Background_Red, IDM_Background_Blue, colorCheck, MF_BYCOMMAND);
        CheckMenuRadioItem(hPMenuBackgroundImg, IDM_Background_Img1, IDM_Background_Img3, imgCheck, MF_BYCOMMAND);

        TrackPopupMenu(hPMenu, TPM_RIGHTBUTTON |
            TPM_TOPALIGN |
            TPM_LEFTALIGN,
            LOWORD(lParam),
            HIWORD(lParam), 0, hWnd, NULL);
        DestroyMenu(hPMenu);
    }
    break;
    case WM_ERASEBKGND:
    {
        DeleteObject(
           (HBRUSH)SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(bkgndcolor))
        );
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    case WM_PAINT:
        {
        HDC hdcInst, hdcBitmap;
        PAINTSTRUCT ps;
        BITMAP bp;
        RECT r;
        hBitmap = LoadBitmap(GetModuleHandle(NULL),
            MAKEINTRESOURCE(image));
        hdcInst = BeginPaint(hWnd, &ps);
        hdcBitmap = CreateCompatibleDC(hdcInst);
        SelectObject(hdcBitmap, hBitmap);
        GetObject(hBitmap, sizeof(bp), &bp);
        GetClientRect(hWnd, &r);
        StretchBlt(hdcInst, 0, 0, r.right - r.left, r.bottom - r.top, hdcBitmap, 0,
            0, bp.bmWidth, bp.bmHeight, SRCCOPY);
        DeleteDC(hdcBitmap);
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
