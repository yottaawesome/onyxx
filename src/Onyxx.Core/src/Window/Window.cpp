#include "pch.hpp"
#include <iostream>
#include <string>
#include "include/Window.hpp"

namespace Onyxx::Core::Window
{
    static std::wstring WindowClassName(L"OnyxxWindowClass");
    static std::wstring WindowTitle(L"Onyxx");

    ATOM RegisterWindowClass(HINSTANCE hInstance)
    {
        WNDCLASSEXW wcex;

        wcex.cbSize = sizeof(WNDCLASSEX);

        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hInstance;
        wcex.hIcon = nullptr;
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_NEPTUNESSPEAR);
        wcex.lpszClassName = WindowClassName.c_str();
        wcex.hIconSm = nullptr;

        return RegisterClassExW(&wcex);
    }

    HWND InitWindow(HINSTANCE hInstance, int nCmdShow)
    {
        HWND hWnd = CreateWindowExW(
            0,
            WindowClassName.c_str(),
            WindowTitle.c_str(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            0,
            CW_USEDEFAULT,
            0,
            nullptr,
            nullptr,
            hInstance,
            nullptr);

        if (hWnd == nullptr)
        {
            std::wcout << L"Failed to create main window" << std::endl;
            return nullptr;
        }

        ShowWindow(hWnd, SW_SHOWNORMAL);
        UpdateWindow(hWnd);

        return hWnd;
    }

    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
            case WM_COMMAND:
            {
                int wmId = LOWORD(wParam);
                break;
            }

            case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);
                // TODO: Add any drawing code that uses hdc here...
                EndPaint(hWnd, &ps);
                break;
            }

            case WM_DESTROY:
            {
                PostQuitMessage(0);
                break;
            }

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
        }
        return 0;
    }
}
