#include <tgaimage.h>
#include <draw.h>
#include <render.h>
#include <model.h>

const TGAColor WHITE = TGAColor(255, 255, 255, 255);
const TGAColor RED = TGAColor(255, 0, 0, 255);
const TGAColor GREEN = TGAColor(0, 255, 0, 255);
const int width = 200;
const int height = 200;

Vec3f world2screen(Vec3f v)
{
	return Vec3f(int((v.x + 1.) * width / 2. + .5), int((v.y + 1.) * height / 2. + .5), v.z);
}

void drawHeadLight(Render& render)
{
	// load .obj
	Model model = Model("D:/Programming/CG/small-software-rasterizer/small-software-rasterizer/small-software-rasterizer/rasterizer/resources/head.obj");

	float* zbuffer = new float[width * height];
	for (int i = width * height; i--; zbuffer[i] = -std::numeric_limits<float>::max());

	Vec3f light_dir(0, 0, -1); // define light_dir
	for (int i = 0; i < model.nfaces(); i++)
	{
		std::vector<int> face = model.face(i);
		Vec3f pts[3];
		Vec3f world_coords[3];
		for (int i = 0; i < 3; i++)
		{
			world_coords[i] = model.vert(face[i]);
			pts[i] = world2screen(model.vert(face[i]));
		}
		// cross product to get normal
		Vec3f n = cross((world_coords[2] - world_coords[0]), (world_coords[1] - world_coords[0]));
		n.normalize();
		// dot product
		float intensity = n * light_dir;
		Draw::drawTriangle(pts, render.renderImage, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255), zbuffer);
	}
}

void drawYDepth(Render& render)
{
	int yBuffer[width];
	for (int i = 0; i < width; ++i)
	{
		yBuffer[i] = std::numeric_limits<int>::min();
	}
	Draw::visulizeYBuffer(Vec2f(20, 34), Vec2f(744, 400), render.renderImage, yBuffer);
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