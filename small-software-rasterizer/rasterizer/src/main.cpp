#include <tgaimage.h>
#include <draw.h>
#include <render.h>
#include <model.h>
#include "matrix.h"

const TGAColor WHITE = TGAColor(255, 255, 255, 255);
const TGAColor RED = TGAColor(255, 0, 0, 255);
const TGAColor GREEN = TGAColor(0, 255, 0, 255);
const int width = 800;
const int height = 800;

vec3f world2screen(vec3f v)
{
	return vec3f(int((v.x + 1.) * width / 2. + .5), int((v.y + 1.) * height / 2. + .5), v.z);
}

void drawHeadLight(Render& render)
{
	// load .obj
	Model model = Model("D:/Programming/CG/small-software-rasterizer/small-software-rasterizer/small-software-rasterizer/rasterizer/resources/head.obj");
	TGAImage texture = TGAImage();
	texture.read_tga_file("D:/Programming/CG/small-software-rasterizer/small-software-rasterizer/small-software-rasterizer/rasterizer/resources/african_head_diffuse.tga");
	texture.flip_vertically();
	vec3f light_dir(0, 0, 1); // define light_dir
	vec3f camera(1, 1, 3);
	vec3f center(0, 0, 0); // in camerea space
	matrix4x4 modelView = Matrix::lookAt(camera, center, vec3f(0, 1, 0)); // object to world
	matrix4x4 projection = Matrix::projection(-1.f / (camera - center).norm()); // world to clip space
	matrix4x4 viewPort = Matrix::viewPort(width / 8, height / 8, width * 3 / 4, height * 3 / 4); // clip to screen

	TGAImage zbuffer(width, height, TGAImage::GRAYSCALE);

	for (int i = 0; i < model.nfaces(); i++)
	{
		std::vector<int> face = model.face(i);
		std::vector<int> uvids = model.coordsId(i);
		std::vector<int> nids = model.normalId(i);
		vec4f pts[3];
		vec3f screen_coords[3];
		vec2f uvs[3];
		vec3f normals[3];
		for (int j = 0; j < 3; j++)
		{
			vec4f vertex;
			for (int k = 0; k < 3; k++) vertex[k] = model.vert(face[j])[k];
			vertex[3] = 1;
			
			vec4f temp = vec4f(viewPort * projection * modelView * vertex);
			pts[j] = temp;
			screen_coords[j] = world2screen(model.vert(face[j]));

			uvs[j] = model.coords(uvids[j]);
			normals[j] = model.normal(nids[j]);
		}
		Draw::drawTriangle(pts, uvs, normals, render.renderImage, texture, light_dir, zbuffer);
	}
	zbuffer.flip_vertically();
	zbuffer.write_tga_file("depth.tga");
}

void drawYDepth(Render& render)
{
	int yBuffer[width];
	for (int i = 0; i < width; ++i)
	{
		yBuffer[i] = std::numeric_limits<int>::min();
	}
	Draw::visulizeYBuffer(vec2f(20, 34), vec2f(744, 400), render.renderImage, yBuffer);
}


int main() {
	// initialize render
	Render render = Render(width, height, TGAImage::RGB);

	//draw something
	drawHeadLight(render);

	// output
	render.renderImage.flip_vertically();
	render.renderImage.write_tga_file("output.tga");
	return 0;
}