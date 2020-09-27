#pragma once

#ifdef ONYXXCORE_EXPORTS
#define ONYXX_API __declspec(dllexport)
#else
#define ONYXX_API __declspec(dllimport)
#endif