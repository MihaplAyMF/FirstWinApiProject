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

    if(!(main_window_handle = CreateWindow(
        L"MainWindowClass",
        L"Button demo",
        WS_POPUP | WS_VISIBLE,
        0, 0,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        NULL, NULL, hInstance, NULL)))
        return 0;

    Game_Init();

    while (TRUE) {

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        Game_Main();

    }

    Game_Shutdown();

    return (msg.wParam);
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

    
    // тут я буду створювати різні віджети якщо треба буде

}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    
    PAINTSTRUCT ps;
    HDC hdc;  
    RECT rect;

    HPEN pen;
    HBRUSH brush;
    
    switch (uMsg) {

        case WM_CREATE:

            hdc = GetDC(hwnd);
            GetClientRect(hwnd, &rect); 
            MainWndAddWudgets(hwnd); // створюємо віджети
            ReleaseDC(hwnd, hdc);
            ValidateRect(hwnd, &rect);
            break;

        case WM_COMMAND:

            // тут можна обробляти параметри меню, кнопок і можливо ще чогось

            switch (wParam) {
                case ID_FILE_EXIT:

                    PostQuitMessage(0);
                    break;
                
                case ID_HELP_ABOUT:
                
                    MessageBox(hwnd, L"It's simple paint", L"About program", MB_OK );
                    break;
                
                default: break;
            }
            break;

        case WM_DESTROY: // вихід з програми
        
            PostQuitMessage(0); 
            break;
        
        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int Game_Init(void* parms, int num_parms){
    return 0;
}

int Game_Main(void* parms, int num_parms){

    if (KEYDOWN(VK_ESCAPE))
        SendMessage(main_window_handle, WM_CLOSE, 0, 0);

    return 0;
}

int Game_Shutdown(void* parms, int num_parms){
    return 0;
}