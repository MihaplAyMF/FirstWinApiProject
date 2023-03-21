#ifndef UNICODE
#define UNICODE
#endif 

#include "function.h"
#include "resource.h"

#define TIMER_ID_1SEC 1

HINSTANCE hinstance_app;
POINT ptPrevious;
COLORREF color = RGB(0, 0, 0);

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

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };

    while (TRUE) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

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

    HPEN pen;
    HBRUSH brush;

    int buttons = (int)wParam;
    int virtual_code = (int)wParam;

    int mouse_x = (int)LOWORD(lParam);
    int mouse_y = (int)HIWORD(lParam);

    switch (uMsg) {

        case WM_CREATE:
            
            SetTimer(hwnd, TIMER_ID_1SEC, 200, NULL);
            break;
        case WM_TIMER:

            switch(wParam){
                case TIMER_ID_1SEC:

                    hdc = GetDC(hwnd);
                    GetClientRect(hwnd, &rect);
                    pen = CreatePen(PS_SOLID, 3, RGB(rand()%400, rand()%400, rand()%400));
                    brush = (HBRUSH) GetStockObject(HOLLOW_BRUSH);
                      
                    SelectObject(hdc, pen);
                    SelectObject(hdc, brush);
                  
                    Ellipse(hdc, rand() % 400, rand() % 400, rand() % 400, rand() % 400);
                    DeleteObject(pen);
                    DeleteObject(brush);
                    ReleaseDC(hwnd, hdc);
                    ValidateRect(hwnd, &rect);

                   
            }
            break;

        case WM_PAINT:

            hdc = GetDC(hwnd);
            ReleaseDC(hwnd, hdc);
            GetClientRect(hwnd, &rect);
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
                case ID_COLOR_RED: 
                    color = RGB(255, 0, 0);
                    break;
                case ID_COLOR_YELLOW:
                    color = RGB(255, 255, 0);
                    break;
                case ID_COLOR_BLUE:
                    color = RGB(0, 0, 255);
                    break;
                case ID_COLOR_GREEN:
                    color = RGB(0, 255, 0);
                    break;
                case ID_COLOR_BLACK:
                    color = RGB(0, 0, 0);
                    break;
                case ID_COLOR_WHITE:
                    color = RGB(255, 255, 255);
                    break;
                case ID_COLOR_LIGHTBLUE:
                    color = RGB(0, 255, 255);
                    break;
                case ID_COLOR_PURPLE:
                   color = RGB(255, 0, 255);
                   break;
                case ID_FILE_EXIT:
                    PostQuitMessage(0);
                    break;
                case ID_HELP_ABOUT:
                    MessageBox(hwnd, L"It's simple paint", L"About program", MB_OK );
                    break;
                default: break;
            }
            break;

        case WM_LBUTTONDOWN:

            hdc = GetDC(hwnd);
            pen = CreatePen(PS_SOLID, 3, color);
            SelectObject(hdc, pen);

            MoveToEx(hdc, mouse_x, mouse_y, NULL);
            LineTo(hdc, mouse_x + 1, mouse_y + 1);

            DeleteObject(pen);
            ReleaseDC(hwnd, hdc);

            ptPrevious.x = mouse_x;
            ptPrevious.y = mouse_y;
            break;

        case WM_RBUTTONDOWN:
            
            hdc = GetDC(hwnd);
            GetClientRect(hwnd, &rect);

            FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW));

            ReleaseDC(hwnd, hdc);
            ValidateRect(hwnd, &rect);
            break;

        case WM_MOUSEMOVE:

            if (buttons & MK_LBUTTON) {
                hdc = GetDC(hwnd);;
                
                pen = CreatePen(PS_SOLID, 3, color);
                SelectObject(hdc, pen);

                MoveToEx(hdc, ptPrevious.x, ptPrevious.y, NULL);
                LineTo(hdc, ptPrevious.x = mouse_x, ptPrevious.y = mouse_y);

                DeleteObject(pen);
                ReleaseDC(hwnd, hdc);

            }
            break;
        
        case WM_SIZE:

            hdc = BeginPaint(hwnd, &ps);
            
            FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(255, 255, 255)));

            EndPaint(hwnd, &ps);
            break;
        case WM_DESTROY:
        
            PostQuitMessage(0);
            PlaySound(NULL, hinstance_app, SND_PURGE);
            break;
        
        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

