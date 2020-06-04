#include "pch.h"
#include "framework.h"
#include "commctrl.h"
#include "Laba4Dll.h"


void sendNames(WPARAM wParam, HWND hendle, char* name) {
    if (HIWORD(wParam) == CBN_SELENDOK)
    {
        int i = SendMessage(hendle, CB_GETCURSEL, 0, 0);
        SendMessage(hendle, CB_GETLBTEXT, i, (LPARAM)name);
    }

}

int button(char* name, char* name2, char* group, HWND hStatus1, HWND hProgress1, HWND hProgress2, int group1Counter, int group2Counter) {
    if (name[0] != NULL && name2[0] != NULL && group[0] != NULL)
    {
        if (group[12] == '1')
        {
            group1Counter++;
            char message[255];
            wsprintf((LPWSTR)message, L"Group 1: %d", group1Counter);
            SendMessage(hStatus1, SB_SETTEXT, 0, (LPARAM)message);
            SendMessage(hProgress1, PBM_STEPIT, 0, 0);
            return group1Counter;
        }
        if (group[12] == '2')
        {
            group2Counter++;
            char message[255];
            wsprintf((LPWSTR)message, L"Group 2: %d", group2Counter);
            SendMessage(hStatus1, SB_SETTEXT, 1, (LPARAM)message);
            SendMessage(hProgress2, PBM_STEPIT, 0, 0);
            return group2Counter;
        }
    }
}
