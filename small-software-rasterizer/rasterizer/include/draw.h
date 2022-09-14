#pragma once
#include <tgaimage.h>

class Draw
{
public:
	// calculate and draw points between (x0,y0) and (x1, y1)
	static void drawLine(int startX, int startY, int endX, int endY, TGAImage& image, const TGAColor& color);
private:
	// Disallow creating an instance of this object
	Draw() {}
};

