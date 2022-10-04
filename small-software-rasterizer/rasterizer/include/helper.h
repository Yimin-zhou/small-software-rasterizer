#pragma once
#include <iostream>

namespace Helper
{
	template<typename T>
	inline void log(T msg)
	{
		std::cout << msg << std::endl;
	}
}
