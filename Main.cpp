#ifndef UNICODE
#define UNICODE
#endif 

#include "function.h"
#include "resource.h"
HINSTANCE hinstance_app;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
  
    srand(time(nullptr));

    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    hinstance_app = hInstance;

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    
    wc.hIcon = LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON1));
    wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
    
    RegisterClass(&wc);

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

    while (TRUE) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){

           if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);

        } 
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;

    int virtual_code = (int)wParam;
    int key_state = (int)lParam;

    char ascii_code = wParam;
    //unsigned int key_state = lParam;

    int width = LOWORD(lParam);
    int height = HIWORD(lParam);

    static int wm_paint_count = 0;
    char text[80] = { '\0' };
    char text2[80] = { '\0' };
    char text3[80] = { '\0' };
    char text4[80] = { '\0' };

    switch (uMsg) {

        case WM_CREATE: 
            
            hdc = GetDC(hwnd);
            GetClientRect(hwnd, &rect);
        
            SetTextColor(hdc, RGB(20, 220, 20));
            SetBkMode(hdc, TRANSPARENT);

            FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 2));

            sprintf(text, "Draw number = %d ", ++wm_paint_count);
            TextOutA(hdc, 10, 20, text, strlen(text));

            sprintf(text2, "WM_SIZE Called - New Size = %d, %d ", width, height);
            TextOutA(hdc, 10, 40, text2, strlen(text2));

            sprintf(text3, "WM_CHAR: Character = %c ", ascii_code);
            TextOutA(hdc, 10, 60, text3, strlen(text3));
            ReleaseDC(hwnd, hdc);
            ValidateRect(hwnd, &rect);
            break;
        case WM_PAINT: 

            hdc = GetDC(hwnd); 
            GetClientRect(hwnd, &rect); 
            
            FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 2));
            
            SetTextColor(hdc, RGB(20, 220, 20));
            SetBkMode(hdc, TRANSPARENT);

            sprintf(text, "Draw number = 0 ", ++wm_paint_count);
            TextOutA(hdc, 10, 20, text, strlen(text));

            sprintf(text2, "WM_SIZE Called - New Size = %d, %d ", width, height);
            TextOutA(hdc, 10, 40, text2, strlen(text2));

            ReleaseDC(hwnd, hdc); 
            ValidateRect(hwnd, &rect); 
 
            break;

        case WM_KEYDOWN:
                
            switch (virtual_code) {
                case VK_RIGHT:
                    PlaySound((LPCTSTR)MAKEINTRESOURCE(IDR_WAVE1), hinstance_app, SND_RESOURCE | SND_ASYNC);
                    break;
                case VK_LEFT:
                    PlaySound(NULL, hinstance_app, SND_PURGE);
                    break;
                case VK_DOWN:
                    PostQuitMessage(WM_QUIT);
                    break;
            }
            break;

        case WM_COMMAND: 

            switch (wParam) {
               case ID_FILE_OPEN:
                   
                    break;
                case ID_FILE_CLOSE:

                    break;
                case ID_FILE_SAVE:

                    break;
                case ID_FILE_EXIT:
                    PostQuitMessage(0);
                    break;
                case ID_HELP_ABOUT:
                    MessageBox(hwnd, L"Так ви не зможете закрити це вікно", L"Що ж сталось?", MB_OK | MB_ICONEXCLAMATION);

                    break;
                default: break;
            }
            break;
        case WM_CHAR:

            hdc = GetDC(hwnd);
            GetClientRect(hwnd, &rect);
            
            SetTextColor(hdc, RGB(20, 220, 20));
            SetBkMode(hdc, TRANSPARENT);

            FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 2));

            sprintf(text, "Draw number = %d ", wm_paint_count);
            TextOutA(hdc, 10, 20, text, strlen(text));

            sprintf(text3, "WM_CHAR: Character = %c ", ascii_code);
            TextOutA(hdc, 10, 60, text3, strlen(text3));

            ReleaseDC(hwnd, hdc);
            ValidateRect(hwnd, &rect);
            break;
        case WM_SIZE:

            hdc = GetDC(hwnd);
            GetClientRect(hwnd, &rect);

            FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 2));

            SetTextColor(hdc, RGB(20, 220, 20));
            SetBkMode(hdc, TRANSPARENT);
          
            sprintf(text, "Draw number = %d ", wm_paint_count);
            TextOutA(hdc, 10, 20, text, strlen(text));

            sprintf(text2, "WM_SIZE Called - New Size = %d, %d ", width, height);
            TextOutA(hdc, 10, 40, text2, strlen(text2));

            ReleaseDC(hwnd, hdc);
            ValidateRect(hwnd, &rect);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            PlaySound(NULL, hinstance_app, SND_PURGE);
            break;
        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

