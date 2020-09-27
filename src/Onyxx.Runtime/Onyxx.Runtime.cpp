#include <iostream>
#include <Windows.h>
#include "Onyxx.Core/include/Window/Window.hpp"
#include "Onyxx.Core/include/D3D/D3D.hpp"

typedef ATOM(*RegisterWindowClassPtr)(HINSTANCE hInstance);
typedef HWND(*InitWindowPtr)(HINSTANCE hInstance);
typedef bool(*PrintHighestFeatureLevelPtr)();

int main(int argc, char** args)
{
    // 1. Load library
    HMODULE coreDll = LoadLibraryW(L"Onyxx.Core.dll");
    if (coreDll == nullptr)
    {
        std::wcout << L"Failed to load Core library" << std::endl;
        return 1;
    }
    
    // 2. Resolve functions
    RegisterWindowClassPtr OnyxxRegisterWindowClass = 
        (RegisterWindowClassPtr)GetProcAddress(coreDll, "RegisterWindowClass");
    if (OnyxxRegisterWindowClass == nullptr)
    {
        std::wcout << L"Failed to load RegisterWindowClass function" << std::endl;
        return 1;
    }

    InitWindowPtr OnyxxInitMainWindow = 
        (InitWindowPtr)GetProcAddress(coreDll, "InitMainWindow");
    if (OnyxxInitMainWindow == nullptr)
    {
        std::wcout << L"Failed to load InitWindow function" << std::endl;
        return 1;
    }

    PrintHighestFeatureLevelPtr OnyxxPrintHighestFeatureLevel = 
        (PrintHighestFeatureLevelPtr)GetProcAddress(coreDll, "PrintHighestFeatureLevel");
    if (OnyxxPrintHighestFeatureLevel == nullptr)
    {
        std::wcout << L"Failed to load OnyxxPrintHighestFeature function" << std::endl;
        return 1;
    }

    // 3. Init main Window
    OnyxxRegisterWindowClass(GetModuleHandleW(nullptr));
    OnyxxInitMainWindow(GetModuleHandleW(nullptr));
    OnyxxPrintHighestFeatureLevel();

    // Main message loop:
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    FreeLibrary(coreDll);

    return (int)msg.wParam;
}

