#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "resource.h"

HINSTANCE hinstance_app;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void Game_Main();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
  

    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    hinstance_app = hInstance;

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    
    wc.hIcon = LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON1));
    wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
    //wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        100, 100, 400, 400,

        NULL,       // Parent window    
        LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)),       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);


    MSG msg = { };

    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }


    while (TRUE) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){

            // Проверка сообщения о выходе
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);

        } 
        // Выполнение игры
        Game_Main();
    }


    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    
    PAINTSTRUCT ps;
    HDC hdc;

    int virtual_code = (int)wParam;
    int key_state = (int)lParam;

    switch (uMsg) {

        case WM_DESTROY:
            PostQuitMessage(0);
            PlaySound(NULL, hinstance_app, SND_PURGE);
            return 0;

        case WM_KEYDOWN:
          
            switch (virtual_code)
            {
                case VK_RIGHT: {
                    PlaySound((LPCTSTR)MAKEINTRESOURCE(IDR_WAVE1), hinstance_app, SND_RESOURCE | SND_ASYNC);
                }
            }

        case WM_PAINT:{

            hdc = BeginPaint(hwnd, &ps);

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 2));

            EndPaint(hwnd, &ps); 
        }

        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void Game_Main(){

}