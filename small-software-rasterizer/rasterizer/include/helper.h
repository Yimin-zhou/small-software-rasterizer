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


	inline Vec3f barycentric(std::vector<Vec3f> vertecies, Vec3f p)
	{
		Vec3f s[2];
		for (int i = 2; i--; )
		{
			s[i][0] = vertecies[2][i] - vertecies[0][i];
			s[i][1] = vertecies[1][i] - vertecies[0][i];
			s[i][2] = vertecies[0][i] - p[i];
		}
		Vec3f u = cross(s[0], s[1]);
		if (std::abs(u[2]) > 1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
			return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
		return Vec3f(-1, 1, 1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
	}
}
