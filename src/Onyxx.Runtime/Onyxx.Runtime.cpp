#include <iostream>
#include <Windows.h>
#include "Onyxx.Core/include/Window.hpp"

typedef ATOM(*RegisterWindowClassPtr)(HINSTANCE hInstance);
typedef HWND(*InitWindowPtr)(HINSTANCE hInstance);

int main(int argc, char** args)
{
    HMODULE coreDll = LoadLibraryW(L"Onyxx.Core.dll");

    if (coreDll == nullptr)
    {
        std::wcout << L"Failed to load Core library" << std::endl;
        return 1;
    }
    
    RegisterWindowClassPtr OnyxxRegisterWindowClass = (RegisterWindowClassPtr)GetProcAddress(coreDll, "RegisterWindowClass");
    InitWindowPtr OnyxxInitMainWindow = (InitWindowPtr)GetProcAddress(coreDll, "InitMainWindow");

    if (OnyxxRegisterWindowClass == nullptr)
    {
        std::wcout << L"Failed to load RegisterWindowClass function" << std::endl;
        return 1;
    }
    if (OnyxxInitMainWindow == nullptr)
    {
        std::wcout << L"Failed to load InitWindow function" << std::endl;
        return 1;
    }

    OnyxxRegisterWindowClass(GetModuleHandleW(nullptr));
    OnyxxInitMainWindow(GetModuleHandleW(nullptr));

    MSG msg;

    // Main message loop:
    while (GetMessageW(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    FreeLibrary(coreDll);

    return (int)msg.wParam;
}

