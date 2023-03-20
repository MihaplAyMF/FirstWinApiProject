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
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);

        }
    }

    return 0;
}


POINT ptPrevious{};
BOOL fDraw = false;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;

    HPEN pen;
    //HBRUSH brush;


    int mouse_x = (int)LOWORD(lParam);
    int mouse_y = (int)HIWORD(lParam);

    int buttons = (int)wParam;

    int virtual_code = (int)wParam;


    //static int wm_paint_count = 0;
    //char text[80] = { '\0' };

    switch (uMsg) {

        /*case WM_CREATE:

            break;*/
        case WM_PAINT:

            hdc = GetDC(hwnd);
            //GetClientRect(hwnd, &rect);

            //FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 2));

            /*SetTextColor(hdc, RGB(20, 220, 20));
            SetBkMode(hdc, TRANSPARENT);*/

            /* sprintf(text, "Draw number = %i ", ++wm_paint_count);
             TextOutA(hdc, 10, 20, text, strlen(text));*/

             /* red_pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
              green_pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
              blue_pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

              red_brush = CreateHatchBrush(HS_VERTICAL, RGB(255, 0, 0));
              old_brush = static_cast<HBRUSH>(SelectObject(hdc, red_brush));

              SelectObject(hdc, blue_pen);

              DeleteObject(red_pen);
              DeleteObject(green_pen);
              DeleteObject(blue_pen);*/


              //pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
              //brush = CreateSolidBrush(RGB(255, 0, 0));
              //SelectObject(hdc, pen);
              //SelectObject(hdc, brush);
              //
              //for (int i = 0; i < 100000; i++) {
              //    
              //    int x0, y0, x1, y1;
              //    x0 = randint(0, 400);
              //    y0 = randint(0, 400);
              //    x1 = randint(0, 400);
              //    y1 = randint(0, 400);

              //    //MoveToEx(hdc, x0, y0, NULL);
              //    //LineTo(hdc, x1, y1  );
              //    

              //    Rectangle(hdc, x0, y0, x1, y1);

              //    DeleteObject(pen);
              //    DeleteObject(brush);
              //    pen = CreatePen(PS_SOLID, 3, RGB(randint(0, 255), randint(0, 255), randint(0, 255)));
              //    brush = CreateSolidBrush(RGB(randint(0, 255), randint(0, 255), randint(0, 255)));
              //    SelectObject(hdc, brush); 
              //    SelectObject(hdc, pen);

              //}

              //DeleteObject(pen);
              //DeleteObject(brush);

            ReleaseDC(hwnd, hdc);
            //ValidateRect(hwnd, &rect); 

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

        case WM_LBUTTONDOWN: 

            hdc = GetDC(hwnd);

            pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
            SelectObject(hdc, pen);

            MoveToEx(hdc, mouse_x, mouse_y, NULL);
            LineTo(hdc, mouse_x+1, mouse_y+1);

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
        case WM_MOUSEMOVE: // переміщаємо кнопку
          
            if (buttons & MK_LBUTTON) {
                hdc = GetDC(hwnd);
               
                pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
                SelectObject(hdc, pen);

                MoveToEx(hdc, ptPrevious.x, ptPrevious.y, NULL);
                LineTo(hdc, ptPrevious.x = mouse_x, ptPrevious.y = mouse_y);
    
                DeleteObject(pen);
                ReleaseDC(hwnd, hdc);
                    
            }  
         
            break;
        //case WM_CHAR:
        //    break;
        //case WM_SIZE:
        //    break;
        case WM_DESTROY:
            PostQuitMessage(0);
            PlaySound(NULL, hinstance_app, SND_PURGE);
            break;
        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

