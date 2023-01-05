#pragma once
#include <tgaimage.h>
#include "geometry.h"
#include <vector>
#include "shader.h"

class Draw
{
public:
	// calculate and draw points between (x0,y0) and (x1, y1)
	//static void drawLine(vec2f v0, vec2f v1, TGAImage& image, const TGAColor& color);
	//// draw triangles method 1
	//static void drawTriangleSweeping(vec2f v0, vec2f v1, vec2f v2, TGAImage& image, const TGAColor& color);
	// draw triangles method 1
	static void drawTriangle(vec4f* pts, vec3f* normals, vec2f* uvs, IShader& shader, TGAImage& image, TGAImage& texture, TGAImage& zBuffer);

	static inline vec3f barycentric(vec2f A, vec2f B, vec2f C, vec2f P)
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

private:
	// Disallow creating an instance of this object
	Draw() {}
};

