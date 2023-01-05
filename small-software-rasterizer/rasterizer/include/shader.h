#pragma once

#include "tgaimage.h"
#include "geometry.h"

class IShader 
{
public:
	vec3f varying_normal; // written by vertex shader, read by fragment shader
	vec2f varying_uv;        // same as above
	virtual vec4f vertex(int iface, int nthvert, matrix4x4 viewport, matrix4x4 projection, matrix4x4 modelView) = 0;
	virtual bool fragment(vec3f bc, TGAColor& color, TGAImage& texture, vec3f normal, vec2f uv) = 0;
};
