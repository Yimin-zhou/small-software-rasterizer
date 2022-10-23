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


	inline vec3f barycentric(vec2f A, vec2f B, vec2f C, vec2f P)
	{
		vec3f s[2];
		for (int i = 2; i--; )
		{
			s[i][0] = C[i] - A[i];
			s[i][1] = B[i] - A[i];
			s[i][2] = A[i] - P[i];
		}
		vec3f u = cross(s[0], s[1]);
		if (std::abs(u[2]) > 1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
			return vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
		return vec3f(-1, 1, 1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
	}
}
