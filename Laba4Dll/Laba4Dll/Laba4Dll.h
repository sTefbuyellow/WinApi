
#pragma once
#ifdef LABA4LIBRARY_EXPORTS
#define LABA4LIBRARY_API __declspec(dllexport)
#else
#define LABA4LIBRARY_API __declspec(dllimport)
#endif




extern "C" LABA4LIBRARY_API void sendNames(WPARAM wParam, HWND hendle, char* name);

extern "C" LABA4LIBRARY_API int button(char* name, char* name2, char* group, HWND hStatus1, HWND hProgress1, HWND hProgress2, int group1Counter, int group2Counter);