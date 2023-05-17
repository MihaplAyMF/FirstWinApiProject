# FirstWinApiProject


#include <iostream>
#include <windows.h>

using namespace std;

//unsigned long sub(char* str) {
//    
//    unsigned long hash1 = 0;
//    int c;
//    while (c = *str++)
//        hash1 = ((hash1 << 5) + hash1) + c;
//    return hash1;
//
//}

#define THREADS_NUMBER 1

DWORD WINAPI Thread(void* p) {

    printf("\n Start thread: %d\n", (unsigned)p);
    while (GetKeyState(VK_CAPITAL) & 0x0001);
    printf("\n End tread: %d", (unsigned)p);
    return NULL;

}


int main() {
    
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    
    DWORD Id;
    HANDLE Handles[THREADS_NUMBER];

    if (GetKeyState(VK_CAPITAL) & 0x0001) printf("\n Caps Off \n");
    else {
        printf("\n Caps Lock turn On");
        return 0;
    }

    for (unsigned i = 0; i < THREADS_NUMBER; i++) {
        Handles[i] = CreateThread(NULL, 0, Thread, (void*)i, 0, &Id);
        printf("\n Thread %04X was created \n", Id);
    }

    WaitForMultipleObjects(THREADS_NUMBER, Handles, true, INFINITE);

    return 0;
}
