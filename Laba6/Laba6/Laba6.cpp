// Laba6.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Laba6.h"
#include "Laba4Dll.h"
#include "commctrl.h"


#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND hComboBoxNames, hComboBox2Names, hComboBoxGroups
, hText1, hProgress1, hProgress2, hStatus1, hStatus2, hButton;
int pParts[2];
char name[255];
char name2[255];
char group[255];
int group1Counter;
int group2Counter;



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
    LoadStringW(hInstance, IDC_LABA6, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LABA6));

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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LABA6));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LABA6);
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
    case WM_CREATE:
    {
        group1Counter = 0;
        group2Counter = 0;

        hStatus1 = CreateWindowEx(0, L"msctls_statusbar32", L"Group 1", WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, 0, NULL, NULL);

        hText1 = CreateWindow(L"STATIC", L"Group 1", WS_CHILD | WS_VISIBLE, 500, 80, 55, 20, hWnd, (HMENU)(-1), NULL, NULL);
        hProgress1 = CreateWindowEx(0, L"msctls_progress32", (LPTSTR)NULL,
            WS_CHILD | WS_VISIBLE, 450, 100, 150, 30,
            hWnd, (HMENU)ID_PROG1, hInst, NULL);
        SendMessage(hProgress1, PBM_SETRANGE, 0, MAKELPARAM(0, 25));
        SendMessage(hProgress1, PBM_SETSTEP, WPARAM(1), 0);

        hText1 = CreateWindow(L"STATIC", L"Group 2", WS_CHILD | WS_VISIBLE, 700, 80, 55, 20, hWnd, (HMENU)(-1), NULL, NULL);
        hProgress2 = CreateWindowEx(0, L"msctls_progress32", (LPTSTR)NULL,
            WS_CHILD | WS_VISIBLE, 650, 100, 150, 30,
            hWnd, (HMENU)ID_PROG1, hInst, NULL);
        SendMessage(hProgress2, PBM_SETRANGE, 0, MAKELPARAM(0, 25));
        SendMessage(hProgress2, PBM_SETSTEP, WPARAM(1), 0);


        hText1 = CreateWindow(L"STATIC", L"Name", WS_CHILD | WS_VISIBLE, 130, 80, 40, 20, hWnd, (HMENU)(-1), NULL, NULL);
        hComboBoxNames = CreateWindow(L"combobox", NULL,
            WS_CHILD | WS_VISIBLE | BS_PUSHBOX,
            50, 100, 200, 200,
            hWnd, (HMENU)ID_LIST1, hInst, NULL);

        hText1 = CreateWindow(L"STATIC", L" Second Name", WS_CHILD | WS_VISIBLE, 100, 180, 100, 20, hWnd, (HMENU)(-1), NULL, NULL);
        hComboBox2Names = CreateWindow(L"combobox", NULL,
            WS_CHILD | WS_VISIBLE | BS_PUSHBOX,
            50, 200, 200, 200,
            hWnd, (HMENU)ID_LIST2, hInst, NULL);

        hText1 = CreateWindow(L"STATIC", L"Group", WS_CHILD | WS_VISIBLE, 130, 280, 40, 20, hWnd, (HMENU)(-1), NULL, NULL);
        hComboBoxGroups = CreateWindow(L"combobox", NULL,
            WS_CHILD | WS_VISIBLE | BS_PUSHBOX,
            50, 300, 200, 200,
            hWnd, (HMENU)ID_LIST3, hInst, NULL);

        hButton = CreateWindow(L"button", L"Send", WS_CHILD | WS_VISIBLE, 100, 350, 100, 20, hWnd, (HMENU)ID_BUTTON, NULL, NULL);

        SendMessage(hComboBoxNames, CB_ADDSTRING, 0,
            (LPARAM)(LPSTR)L"Киря");
        SendMessage(hComboBoxNames, CB_ADDSTRING, 1,
            (LPARAM)(LPSTR)L"Филя");
        SendMessage(hComboBoxNames, CB_ADDSTRING, 2,
            (LPARAM)(LPSTR)L"Пупа");
        SendMessage(hComboBoxNames, CB_ADDSTRING, 3,
            (LPARAM)(LPSTR)L"Лупа");
        SendMessage(hComboBoxNames, CB_ADDSTRING, 4,
            (LPARAM)(LPSTR)L"Степанос");

        SendMessage(hComboBox2Names, CB_ADDSTRING, 0,
            (LPARAM)(LPSTR)L"Иствуд");
        SendMessage(hComboBox2Names, CB_ADDSTRING, 1,
            (LPARAM)(LPSTR)L"Джилленхол");
        SendMessage(hComboBox2Names, CB_ADDSTRING, 2,
            (LPARAM)(LPSTR)L"Котиков");
        SendMessage(hComboBox2Names, CB_ADDSTRING, 3,
            (LPARAM)(LPSTR)L"Медведев");
        SendMessage(hComboBox2Names, CB_ADDSTRING, 4,
            (LPARAM)(LPSTR)L"Джобс");


        SendMessage(hComboBoxGroups, CB_ADDSTRING, 1,
            (LPARAM)(LPSTR)L"Group 1");
        SendMessage(hComboBoxGroups, CB_ADDSTRING, 2,
            (LPARAM)(LPSTR)L"Group 2");
        break;
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:


        switch (LOWORD(wParam))
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case ID_LIST3:
            sendNames(wParam, hComboBoxGroups, group);
            break;
        case ID_LIST1:
            sendNames(wParam, hComboBoxNames, name);
            break;
        case ID_LIST2:
            sendNames(wParam, hComboBox2Names, name2);
            break;
        case ID_BUTTON:
            if (name[0] != NULL && name2[0] != NULL && group[0] != NULL)
            {
                if (group[12] == '1')
                {
                    group1Counter++;
                    char message[255];
                    wsprintf((LPWSTR)message, L"Group 1: %d", group1Counter);
                    SendMessage(hStatus1, SB_SETTEXT, 0, (LPARAM)message);
                    SendMessage(hProgress1, PBM_STEPIT, 0, 0);
                }
                if (group[12] == '2')
                {
                    group2Counter++;
                    char message[255];
                    wsprintf((LPWSTR)message, L"Group 2: %d", group2Counter);
                    SendMessage(hStatus1, SB_SETTEXT, 1, (LPARAM)message);
                    SendMessage(hProgress2, PBM_STEPIT, 0, 0);
                }
                UpdateWindow(hProgress1);
            }
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_SIZE:
        RECT rect;
        GetClientRect(hWnd, &rect);
        int pParts[2];
        pParts[0] = rect.right / 2; //часть 1 
        pParts[1] = -1; // часть 2

        SendMessage(hStatus1, SB_SETPARTS, 2, (LPARAM)pParts);
        SendMessage(hStatus1, WM_SIZE, wParam, lParam);
        SendMessage(hStatus1, SB_SETTEXT, 1, (LPARAM)L"Group 2");
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
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
