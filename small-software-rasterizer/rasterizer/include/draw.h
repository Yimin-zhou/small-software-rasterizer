#pragma once
#include <tgaimage.h>
#include "geometry.h"
#include <vector>

class Draw
{
public:
	// calculate and draw points between (x0,y0) and (x1, y1)
	static void drawLine(vec2f v0, vec2f v1, TGAImage& image, const TGAColor& color);
	// draw triangles method 1
	static void drawTriangleSweeping(vec2f v0, vec2f v1, vec2f v2, TGAImage& image, const TGAColor& color);
	// draw triangles method 1
	static void drawTriangle(vec4f* pts, vec2f* uvs, vec3f* normals, TGAImage& image, TGAImage& texture, const vec3f lightDir, TGAImage& zBuffer);

	// depth
	// ybuffer (2D test)
	static void visulizeYBuffer(vec2f p0, vec2f p1, TGAImage& image, int yBuffer[]);

private:
	// Disallow creating an instance of this object
	Draw() {}
};

