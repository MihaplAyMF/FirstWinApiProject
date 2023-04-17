#ifndef UNICODE
#define UNICODE
#endif 

#include "function.h"

struct ButtonCoordinates {
    int x;
    int y;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    WNDCLASS wc;

    wc.style = NULL;
    wc.hbrBackground = CreateSolidBrush(RGB(100, 100, 100));
    wc.hCursor = LoadCursor(NULL, 0);
    wc.hInstance = hInstance;
    wc.hIcon = LoadIconA(hInstance, 0);
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.lpszClassName = L"MainWindowClass";
    wc.lpfnWndProc = WindowProc;
    wc.lpszMenuName = 0;

    MSG msg;
    timerInterval = 1000;
    hInstance_app = hInstance;
    srand(time(nullptr));

    RegisterClass(&wc);
    globalHwnd = CreateWindowEx(
        0,
        L"MainWindowClass",
        L"Button Subclassing",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100,
        100,
        400,
        400,
        NULL,
        NULL,
        hInstance_app,
        NULL);

    ShowWindow(globalHwnd, 1);
    UpdateWindow(globalHwnd);

    while (TRUE) {

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

    }
    return msg.wParam;
}

void MainWndAddWudgets(HWND hwnd) {

    hButClick = CreateWindowA("button", "1000", WS_CHILD | WS_VISIBLE, rand() % 320, rand() % 300, 50, 25, hwnd, (HMENU)BUTTON_ONE_CLICK, hInstance_app, NULL);
   // hText = CreateWindowA("Static", "Click", WS_VISIBLE | WS_CHILD | ES_CENTER, 20, 20, 50, 50, hwnd, NULL, NULL, NULL);
    original_procedure = (WNDPROC)SetWindowLong(hButClick, GWL_WNDPROC, (long)ButtonProc);

}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

    RECT rect;
    ButtonCoordinates buttonCoords;

    switch (Message) {

        case WM_CREATE:

            MainWndAddWudgets(hwnd);
            break;


        case WM_TIMER: 
            switch (wParam) {
                case TIMER_ID_ONE: {
                 
                    POINT cursorPos;
                    GetCursorPos(&cursorPos);
                    ScreenToClient(globalHwnd, &cursorPos);

                    GetWindowRect(hButClick, &rect);
                    buttonCoords.x = rect.right - rect.left;
                    buttonCoords.y = rect.bottom - rect.top;
                    ScreenToClient(globalHwnd, &cursorPos);
                    int newX = rand() % 320;
                    int newY = rand() % 300;
                    MoveWindow(hButClick, newX, newY, buttonCoords.x, buttonCoords.y, TRUE);

                    KillTimer(globalHwnd, TIMER_ID_ONE);
                } break;
               
                default: break;
            } 

            break;

        case WM_MOUSEMOVE:

            if (toggle == true) {

                toggle = false;
               
            }
            break;

        case WM_DESTROY:

            KillTimer(globalHwnd, timerId);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
}

LRESULT CALLBACK ButtonProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
  
    RECT rect;
    ButtonCoordinates buttonCoords;

    switch (Message) {

        case WM_LBUTTONDOWN: {

            POINT cursorPos;
            GetCursorPos(&cursorPos);
            ScreenToClient(globalHwnd, &cursorPos);
 
            GetWindowRect(hButClick, &rect);
            buttonCoords.x = rect.right - rect.left;
            buttonCoords.y = rect.bottom - rect.top;
            ScreenToClient(globalHwnd, &cursorPos);
            int newX = rand() % 320;
            int newY = rand() % 300;
            MoveWindow(hButClick, newX, newY, buttonCoords.x, buttonCoords.y, TRUE);

            timerInterval /= 2.0;

            char buf[10]; // буфер для зберігання тексту
            sprintf(buf, "%d", timerInterval); // перетворення змінної на рядок
            SetWindowTextA(hButClick, buf);

            KillTimer(globalHwnd, TIMER_ID_ONE);
            break; }
   
        case WM_MOUSEMOVE:

            if (toggle == false) {

                toggle = true;
                startTime = GetTickCount();
                timerId = SetTimer(globalHwnd, TIMER_ID_ONE, timerInterval, NULL);
            }
            break;

    }
    return CallWindowProc(original_procedure, hwnd, Message, wParam, lParam);
}
