#include <string>

#include <windows.h>

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PSTR lpCmdLine, INT nCmdShow)
{
    auto message = [](const std::string &message)
    {
        MessageBoxA(nullptr, message.c_str(), "Payload", 0);
    };

    message("Hello World!");

    return 0;
}