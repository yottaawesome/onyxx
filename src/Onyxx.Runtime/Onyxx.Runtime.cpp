#include <iostream>
#include <Windows.h>
#include "Onyxx.Core/include/Window.hpp"

typedef ATOM(*RegisterWindowClassPtr)(HINSTANCE hInstance);
typedef HWND(*InitWindowPtr)(HINSTANCE hInstance, int show);

int main(int argc, char** args)
{
    HMODULE coreDll = LoadLibraryW(L"Onyxx.Core.dll");

    if (coreDll == nullptr)
    {
        std::wcout << L"Failed to load Core library" << std::endl;
        return 1;
    }
    
    RegisterWindowClassPtr regType = (RegisterWindowClassPtr)GetProcAddress(coreDll, "RegisterWindowClass");
    InitWindowPtr initType = (InitWindowPtr) GetProcAddress(coreDll, "InitWindow");

    if (regType == nullptr)
    {
        std::wcout << L"Failed to load RegisterWindowClass function" << std::endl;
        return 1;
    }
    if (initType == nullptr)
    {
        std::wcout << L"Failed to load InitWindow function" << std::endl;
        return 1;
    }

    regType(GetModuleHandleW(nullptr));
    initType(GetModuleHandleW(nullptr), 0);

    Sleep(3000);

    //FreeLibrary(coreDll);

    return 0;
}

