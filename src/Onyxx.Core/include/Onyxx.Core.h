#pragma once

#ifdef ONYXXCORE_EXPORTS
#define ONYXX_API __declspec(dllexport)
#else
#define ONYXX_API __declspec(dllimport)
#endif

namespace Onyxx
{
	class ONYXX_API IOnyxx
	{
	public:
		virtual ~IOnyxx() = 0;
	};

	extern "C" ONYXX_API [[nodiscard]] IOnyxx* GetMainInterface();
}
