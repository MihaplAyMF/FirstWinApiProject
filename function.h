#pragma once

#pragma warning(disable : 4996)

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <ctime>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int randint(int start, int end) {
	return rand() % end + start;
}

//void Game_Main();