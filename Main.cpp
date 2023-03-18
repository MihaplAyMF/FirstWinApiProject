#ifndef UNICODE
#define UNICODE
#endif 

#include "function.h"
#include "resource.h"

HINSTANCE hinstance_app;

//BOOL TextOut(HDC hdc, int nxStart, int nyStart, LPCTSTR lpString, int cbString);



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
  
    srand(time(nullptr));

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

    RECT rect;
    HDC hdc = GetDC(hwnd);
    COLORREF old_fcolor, old_bcolor;
    
    GetClientRect(hwnd, &rect);
    FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 2)); 
    SetBkMode(hdc, TRANSPARENT);
    while (TRUE) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){

           if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);

        } 
      
      
        SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
        
        TextOut(hdc, randint(0, 400), randint(0, 400), L"Hello world!", strlen("Hello world!"));

        Sleep(100);

    }

    ReleaseDC(hwnd, hdc);

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;

    int virtual_code = (int)wParam;
    int key_state = (int)lParam;


    COLORREF old_fcolor, old_bcolor; 
    int old_tmode;

    switch (uMsg) {


        case WM_CREATE: 
            break;
        case WM_PAINT: 
                

            GetClientRect(hwnd, &rect); 
            hdc = GetDC(hwnd); 

           //FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 2));

            /*old_fcolor = SetTextColor(hdc, RGB(0, 255, 0));
            old_bcolor = SetBkColor(hdc, RGB(0, 0, 0));
            old_tmode = SetBkMode(hdc, TRANSPARENT);

            SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
            SetBkColor(hdc, RGB(0, 0, 0));
            SetBkMode(hdc, TRANSPARENT);

            TextOut(hdc, randint(0, 400), randint(0, 400), L"HelloWorld", strlen("HelloWorld"));
            TextOut(hdc, 50, 80, L"HelloWorld", strlen("HelloWorld"));
            
            Sleep(100);*/

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
                    MessageBox(hwnd, L"Menu Sound Demo", L"About Sound Menu", MB_OK | MB_ICONEXCLAMATION);

                    break;
                default: break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            PlaySound(NULL, hinstance_app, SND_PURGE);
            break;
        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

}

//void Game_Main(){
//
//}

