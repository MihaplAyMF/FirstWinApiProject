
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>

int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow) {

	MessageBox(NULL, L"THERE CAN BE ONLY ONE!!!", L"MY FIRST WINDOWS PROGRAM", MB_OK | MB_ICONEXCLAMATION);


	return(0);
}