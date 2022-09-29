#pragma once
#include <tgaimage.h>
#include "geometry.h"

class Draw
{
public:
	// calculate and draw points between (x0,y0) and (x1, y1)
	static void drawLine(Vec2i v0, Vec2i v1, TGAImage& image, const TGAColor& color);
	// draw triangles method 1
	static void drawTriangleSweeping(Vec2i v0, Vec2i v1, Vec2i v2, TGAImage& image, const TGAColor& color);
	// draw triangles method 1
	static void drawTriangle(Vec2i v0, Vec2i v1, Vec2i v2, TGAImage& image, const TGAColor& color);
private:
	// Disallow creating an instance of this object
	Draw() {}
};

