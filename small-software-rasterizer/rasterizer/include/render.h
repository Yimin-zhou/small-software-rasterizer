#pragma once
#include <tgaimage.h>

class Render
{
public:
	Render(int width, int height, TGAImage::Format format);

	int renderWidth, renderHeight;
	TGAImage renderImage;
};

inline Render::Render(int width, int height, TGAImage::Format format)
{
	renderWidth = width;
	renderHeight = width;
	renderImage = TGAImage(width, height, format);
}

