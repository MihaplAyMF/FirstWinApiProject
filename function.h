#pragma once

#pragma warning(disable : 4996)

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <ctime>

#define TIMER_ID_1SEC 1
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400
#define ON_READ_FIELD 2
#define ON_CLEAR_FIELD 3
#define TEXT_BUFFER 10

#define KEYDOWN(vk_code) \
 ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code) \
 ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

char buffer[TEXT_BUFFER];
HINSTANCE hInstance_app; 
HWND main_window_handle; // дескриптор вікна

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
WNDCLASS NewWindowClass(HBRUSH BGcolor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
void MainWndAddWudgets(HWND hwnd);

int Game_Init(void* parms = NULL, int num_parms = 0);
int Game_Main(void* parms = NULL, int num_parms = 0);
int Game_Shutdown(void* parms = NULL, int num_parms = 0);

int randint(int start, int end) {
	return rand() % end + start;
}
