#pragma once
#include "Macros.hpp"
#include <Windows.h>

namespace Onyxx::Core::Window
{
	extern "C" ONYXX_API ATOM				RegisterWindowClass(HINSTANCE hInstance);
	extern "C" ONYXX_API HWND               InitWindow(HINSTANCE, int);
	extern "C" ONYXX_API LRESULT CALLBACK   WndProc(HWND, UINT, WPARAM, LPARAM);
}