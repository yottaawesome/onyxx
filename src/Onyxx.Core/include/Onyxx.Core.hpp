#pragma once
#include "Macros.hpp"

namespace Onyxx
{
	class ONYXX_API IOnyxx
	{
	public:
		virtual ~IOnyxx() = 0;
	};

	extern "C" ONYXX_API [[nodiscard]] IOnyxx* GetMainInterface();
}
