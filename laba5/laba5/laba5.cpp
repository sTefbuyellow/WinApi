// laba5.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "laba5.h"
#include  <mutex>
#include "processthreadsapi.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

STARTUPINFO si = { 0 };
PROCESS_INFORMATION hProcess = { 0 };
STARTUPINFO si1 = { 0 };
PROCESS_INFORMATION hProcess1 = { 0 };
HGDIOBJ BRUHsh;
HFONT BRUHfont;
HWND timer, hButton1, hButton2, hButton3;
HANDLE hFile, hFile2;
OVERLAPPED olf = { 0 };
LARGE_INTEGER li = { 0 };
LPDWORD readed = 0;
LPSTR buff;
LPSTR buff2;
HANDLE h1, h2, h3;
DWORD numred1, numred2;
int numbers = 0;
int numbers2 = 0;
int x, y;

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
    LoadStringW(hInstance, IDC_LABA5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LABA5));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LABA5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LABA5);
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


void OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam){
    RECT rect;
    switch (wParam)
    {
    case 1:
        GetClientRect(hWnd, &rect);
        x -= 10;
        if (x < rect.left - 2000) {
            x = rect.right;
        }
        InvalidateRect(hWnd, &rect, FALSE);
        break;
    }
}

VOID CALLBACK onReadComplete(
    DWORD dwErrorCode,
    DWORD dwNumberOfBytesTransfered,
    LPOVERLAPPED lpOverlapped) {
    return;
}

DWORD WINAPI ReadFileAndGetNumber(LPVOID param) {
    hFile = CreateFile(L"test.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    //SetFilePointer(hFile, FILE_END, NULL, FILE_BEGIN);
   /* li.QuadPart = 0;
    olf.Offset = li.LowPart;
    olf.OffsetHigh = li.HighPart;*/
    buff = (CHAR*)malloc(sizeof(CHAR)* 1073741825);
    OVERLAPPED oOverlap;
    uint8_t read_data[1024];
    if (ReadFileEx(hFile, (LPVOID)read_data, 10, (LPOVERLAPPED)&oOverlap, onReadComplete)) {
        int i = 0;
        while (buff[i] != '\r') {
            if ((int)buff[i] >= 48 && (int)buff[i] <= 57)
                numbers++;
            i++;
        }
        wchar_t str[80];
        wsprintf(str, L"%d", numbers);
        MessageBox((HWND)param, str, L"", NULL);
        delete buff;
        numbers = 0;
    }else MessageBox((HWND)param, L"1", L"Error", NULL);
    ExitThread(0);
}

DWORD WINAPI ReadFileAndGetNumber2(LPVOID param) {
    hFile2 = CreateFile(L"test2.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    SetFilePointer(hFile2, FILE_END, NULL, FILE_BEGIN);
 /*   li.QuadPart = 0;
    olf.Offset = li.LowPart;
    olf.OffsetHigh = li.HighPart;*/
    buff2 = (CHAR*)malloc(sizeof(CHAR) * 1073741825);
    if (ReadFile(hFile2, buff2, 1073741825, &numred2, NULL)) {
        int i = 0;
        while (buff2[i] != '\r') {
            if ((int)buff2[i] >= 48 && (int)buff2[i] <= 57)
                numbers2++;
            i++;
        }
        wchar_t str2[80];
        wsprintf(str2, L"%d", numbers2);
        MessageBox((HWND)param, str2, L"", NULL);
        delete buff2;
        numbers2 = 0;
    }else MessageBox((HWND)param, L"2", L"Error", NULL);
    ExitThread(0);
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        HMENU hMenu = CreateMenu();
        RECT rect;
        GetClientRect(hWnd, &rect);
        x = rect.right;
        y = 0;
        BRUHsh = CreateSolidBrush(RGB(255, 255, 255));
        BRUHfont = CreateFont(-48, 0, GM_COMPATIBLE, 0, FW_DONTCARE, 0, 0, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"consolas");
        SetTimer(hWnd, 1, 100, NULL);
        hButton1 = CreateWindow(L"button", L"Button №1", WS_CHILD | WS_VISIBLE, 100, 350, 100, 20, hWnd, (HMENU)ID_BUTTON1, NULL, NULL);
        hButton2 = CreateWindow(L"button", L"Button №2", WS_CHILD | WS_VISIBLE, 200, 350, 100, 20, hWnd, (HMENU)ID_BUTTON2, NULL, NULL);
        hButton3 = CreateWindow(L"button", L"Button №3", WS_CHILD | WS_VISIBLE, 300, 350, 100, 20, hWnd, (HMENU)ID_BUTTON3, NULL, NULL);
        break;
    }
    case WM_TIMER:
        OnTimer(hWnd, wParam, lParam);
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
            case ID_1488:
                CreateProcess(L"C:\\Windows\\system32\\mspaint.exe", NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &hProcess);
                CreateProcess(L"C:\\Windows\\system32\\calc.exe", NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si1, &hProcess1);
                break;
            case ID_BUTTON1: 
                hFile = CreateFile(L"test1.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                li.QuadPart = 0;
                olf.Offset = li.LowPart;
                olf.OffsetHigh = li.HighPart;
                buff = (CHAR*)malloc(sizeof(CHAR)* 1073741825);
                if (ReadFile(hFile, buff, 1073741825, readed, &olf)) {
                    int i = 0;
                    while (buff[i] != '\r') {
                        if ((int)buff[i] >= 48 && (int)buff[i] <= 57)
                        numbers++;
                        i++;
                    }
                    wchar_t str[80];
                    wsprintf(str, L"%d", numbers);
                    MessageBox(hWnd, str, L"", NULL);
                    delete buff;
                    numbers = 0;
                    hFile = NULL;
                }
                break;
            case ID_BUTTON2:
                h1 = CreateThread(NULL, 0, ReadFileAndGetNumber, hWnd, 0, 0);
                CloseHandle(h1);
                break;
            case ID_BUTTON3:
                SetThreadPriority(h2, THREAD_PRIORITY_HIGHEST);
                SetThreadPriority(h3, THREAD_PRIORITY_BELOW_NORMAL);
                h2 = CreateThread(NULL, 0, ReadFileAndGetNumber, (LPVOID)hWnd, 0, NULL);
                h3 = CreateThread(NULL, 0, ReadFileAndGetNumber2, (LPVOID)hWnd, 0, NULL);
                
                CloseHandle(h2);
                CloseHandle(h3);
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
            RECT rect;
            HGDIOBJ oldBRUHsh;
            HFONT oldBRUHfont;
            const wchar_t* text = L"Yea boiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii";
            GetClientRect(hWnd, &rect);
            oldBRUHsh = (HGDIOBJ)SelectObject(hdc, BRUHsh);
            oldBRUHfont = (HFONT)SelectObject(hdc, BRUHfont);

            SetTextColor(hdc, RGB(0, 0, 0));
            SetBkMode(hdc, TRANSPARENT);

            Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
            TextOut(hdc, x, y, text, wcslen(text));

            SelectObject(hdc, oldBRUHsh);
            SelectObject(hdc, oldBRUHfont);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        TerminateProcess(hProcess.hProcess, 9);
        CloseHandle(hProcess.hProcess);
        CloseHandle(hProcess.hThread);
        CloseHandle(hProcess1.hProcess);
        CloseHandle(hProcess1.hThread);
        DeleteObject(BRUHfont);
        DeleteObject(BRUHsh);
        KillTimer(timer, 1);
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
