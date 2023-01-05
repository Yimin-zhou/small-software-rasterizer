#pragma once
#include <iostream>

namespace Helper
{
	template<typename T>
	inline void log(T msg)
	{
		std::cout << msg << std::endl;
	}

	inline int getIndexOffset(int x, int y, int width)
	{
		return x + y * width;
	}
}
