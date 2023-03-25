#ifndef UNICODE
#define UNICODE
#endif 

#include "function.h"
#include "resource.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    WNDCLASS wc = NewWindowClass((HBRUSH)(COLOR_WINDOW + 2), LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1)), hInstance,
                                 LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON1)), L"MainWindowClass", WindowProc);

    if(!RegisterClass(&wc)) {return -1;}

    hInstance_app = hInstance;
    MSG msg = { 0 };

    CreateWindow(
        L"MainWindowClass",                                 // Window class
        L"First c++ window",                                // Window text
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,                   // Window style
        100, 100, 400, 400,                                 // Size and position
        NULL,                                               // Parent window
        NULL,//LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)),    // Menu
        hInstance,                                          // Instance handle
        NULL                                                // Additional application data
    );

    while (TRUE) {

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

    }

    //DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, WindowProc, 0);

    return 0;
}

WNDCLASS NewWindowClass(HBRUSH BGcolor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure){
    
    WNDCLASS wc = {};

    wc.hbrBackground = BGcolor;
    wc.hCursor = Cursor;
    wc.hInstance = hInst;
    wc.hIcon = Icon;
    wc.lpszClassName = Name;
    wc.lpfnWndProc = WindowProc;

    return wc;
}

void MainWndAddWudgets(HWND hwnd){
   
    oneStatic = CreateWindowA("Static", "Input text", WS_CHILD | WS_VISIBLE | ES_CENTER,
        150, 17, 100, 24, hwnd, NULL, NULL, NULL
    );     

    oneEdit = CreateWindowA("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE /*| ES_MULTILINE | WS_VSCROLL*/,
        15, 50, 200/*350*/, 24/*100*/, hwnd, NULL, NULL, NULL
    ); 

    CreateWindowA("Button", "Clear", WS_VISIBLE | WS_CHILD | ES_CENTER,
        15, 85, 100, 24, hwnd, (HMENU)ON_CLEAR_FIELD, NULL, NULL
    );

    CreateWindowA("Button", "Read", WS_VISIBLE | WS_CHILD | ES_CENTER,
        15, 15, 100, 24, hwnd, (HMENU)ON_READ_FIELD, NULL, NULL
    );



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
            hdc = GetDC(hwnd);
            GetClientRect(hwnd, &rect);
            //SetBkColor(hdc, RGB(255, 0, 0));
            MainWndAddWudgets(hwnd);
            ReleaseDC(hwnd, hdc);
            ValidateRect(hwnd, &rect);

            break;
        case WM_COMMAND:
            switch (wParam) {
               /* case ID_FILE_EXIT:
                    PostQuitMessage(0);
                    break;
                case ID_HELP_ABOUT:
                    MessageBox(hwnd, L"It's simple paint", L"About program", MB_OK );
                    break;*/
                case ON_CLEAR_FIELD:
                    SetWindowTextA(oneEdit, "");
                    break;
                case ON_READ_FIELD:
                    GetWindowTextA(oneEdit, buffer, TEXT_BUFFER);
                    SetWindowTextA(oneStatic, buffer);
                    break;
                default: break;
            }
            break;
       /* case WM_CTLCOLORSTATIC: {
            HDC hdcStatic = (HDC)wParam;
            SetBkMode(hdcStatic, RGB(0, 0, 0));
            return (LRESULT)GetStockObject(NULL_BRUSH);
        
        }*/
        case WM_CTLCOLORSTATIC:
            SetBkColor((HDC)wParam, RGB(100, 100, 100));
            return (LRESULT)CreateSolidBrush(RGB(100, 100, 100));
            break;
        case WM_DESTROY:
        
            PostQuitMessage(0);
            break;
        
        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

