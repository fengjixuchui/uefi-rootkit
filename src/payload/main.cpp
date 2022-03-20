#include <windows.h>

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PSTR lpCmdLine, INT nCmdShow)
{
    MessageBoxA(nullptr, "Hello World!", "payload", 0);

    return 0;
}