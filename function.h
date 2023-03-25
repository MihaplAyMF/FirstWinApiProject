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

char buffer[TEXT_BUFFER];

POINT ptPrevious;
COLORREF color = RGB(100, 100, 100);
HINSTANCE hInstance_app;
HWND oneEdit;
HWND oneStatic;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
WNDCLASS NewWindowClass(HBRUSH BGcolor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
void MainWndAddWudgets(HWND hwnd);

int randint(int start, int end) {
	return rand() % end + start;
}
