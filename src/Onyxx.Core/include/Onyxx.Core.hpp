#pragma once
#include "Macros.hpp"
#include "D2D/D2D.hpp"
#include "D3D/D3D.hpp"
#include "Window/Window.hpp"

namespace Onyxx
{
	class ONYXX_API IOnyxx
	{
		public:
			virtual ~IOnyxx() = 0;
	};

	extern "C" ONYXX_API [[nodiscard]] IOnyxx* GetMainInterface();
}
