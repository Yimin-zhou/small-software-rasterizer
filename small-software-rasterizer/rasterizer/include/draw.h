#pragma once
#include <tgaimage.h>
#include "geometry.h"
#include <vector>

class Draw
{
public:
	// calculate and draw points between (x0,y0) and (x1, y1)
	static void drawLine(Vec2f v0, Vec2f v1, TGAImage& image, const TGAColor& color);
	// draw triangles method 1
	static void drawTriangleSweeping(Vec2f v0, Vec2f v1, Vec2f v2, TGAImage& image, const TGAColor& color);
	// draw triangles method 1
	static void drawTriangle(Vec3f v0, Vec3f v1, Vec3f v2, TGAImage& image, const TGAColor& color, float* zBuffer);

	// depth
	// ybuffer (2D test)
	static void visulizeYBuffer(Vec2f p0, Vec2f p1, TGAImage& image, int yBuffer[]);

private:
	// Disallow creating an instance of this object
	Draw() {}
};

