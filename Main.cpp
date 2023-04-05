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
        L"Write and save txt files",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 
        100,
        400,
        400,
        NULL, LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)), hInstance, NULL)))
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

    CreateWindowA("Button", "Save", WS_VISIBLE | WS_CHILD | ES_CENTER, 10, 10, 100, 30, hwnd, (HMENU)BUTTON_ONE_CLICK, NULL, NULL);
    CreateWindowA("Button", "Load", WS_VISIBLE | WS_CHILD | ES_CENTER, 150, 10, 100, 30, hwnd, (HMENU)BUTTON_TWO_CLICK, NULL, NULL);


    hEditOne = CreateWindowA("Edit", " ", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL, 10, 50, 300, 130, hwnd, NULL, NULL, NULL);
    
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
            SetOpenFileParams(hwnd);
            ReleaseDC(hwnd, hdc);
            ValidateRect(hwnd, &rect);
            break;

        case WM_COMMAND:

            // тут можна обробляти параметри меню, кнопок і можливо ще чогось

            switch (wParam) {

                case ID_FILE_EXIT:

                    PostQuitMessage(0);
                    break;
                
                case BUTTON_ONE_CLICK:
                    if (GetSaveFileNameA(&ofn)) { SaveData(fileName); }
                    break;

                case BUTTON_TWO_CLICK:
                    if (GetOpenFileNameA(&ofn)) { LoadData(fileName); }
                    break;
                
                case ID_FILE_SAVE:

                    if (GetSaveFileNameA(&ofn)) { SaveData(fileName); }
                    break;

                case ID_FILE_OPEN:

                    if (GetOpenFileNameA(&ofn)) { LoadData(fileName); }
                    break;

                case ID_FILE_CLOSE:

                    PostQuitMessage(0);
                    break;
                
                case ID_HELP_ABOUT:
                    MessageBox(hwnd, L"It's simple paint", L"About program", MB_OK );
                    break;
                
                default: break;
            }
            break;

        case WM_CTLCOLORSTATIC:
            SetBkColor((HDC)wParam, RGB(100, 100, 100));
            return (LRESULT) CreateSolidBrush(RGB(100, 100, 100));
            break;

        case WM_DESTROY: // вихід з програми
        
            PostQuitMessage(0); 
            break;
        
        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}


void SaveData(LPCSTR path){
    
    HANDLE FileToSave = CreateFileA(path, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    int saveLength = GetWindowTextLength(hEditOne) + 1;
    char* data = new char[saveLength];
    saveLength = GetWindowTextA(hEditOne, data, saveLength);

    DWORD bytesIterated;

    WriteFile(FileToSave, data, saveLength, &bytesIterated, NULL);

    CloseHandle(FileToSave);
    delete[] data;
}
 
void LoadData(LPCSTR path){
    HANDLE FileToLoad = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    DWORD fileSize = GetFileSize(FileToLoad, NULL);
    char* data = new char[fileSize + 1];

    DWORD bytesRead;
    ReadFile(FileToLoad, data, fileSize, &bytesRead, NULL);

    data[fileSize] = '\0';
    SetWindowTextA(hEditOne, data);

    CloseHandle(FileToLoad);
    delete[] data;
     
}

void SetOpenFileParams(HWND hWnd) {
   
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
    ofn.lpstrDefExt = "txt";
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