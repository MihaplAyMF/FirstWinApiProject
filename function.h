#pragma once

#pragma warning(disable : 4996)

#include <windows.h>
#include <ctime>
#include <stdio.h>

#define TIMER_ID_ONE 1
#define BUTTON_ONE_CLICK 5

HINSTANCE hInstance_app;
HWND globalHwnd, hButClick, hText;
WNDPROC original_procedure;
UINT_PTR timerId;
DWORD timerInterval, currentTime, startTime;
bool toggle = false, state = true;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ButtonProc(HWND, UINT, WPARAM, LPARAM);
void MainWndAddWudgets(HWND hwnd);
