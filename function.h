#pragma once

#include <windows.h>
#include <ctime>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int randint(int start, int end) {
	return rand() % end + start;
}

//void Game_Main();