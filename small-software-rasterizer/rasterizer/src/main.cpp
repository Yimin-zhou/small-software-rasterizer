#include <tgaimage.h>
#include <draw.h>
#include <render.h>
#include <model.h>

const TGAColor WHITE = TGAColor(255, 255, 255, 255);
const TGAColor RED = TGAColor(255, 0, 0, 255);
const TGAColor GREEN = TGAColor(0, 255, 0, 255);
const int width = 200;
const int height = 200;

void drawHead(Render& render)
{
	// load .obj
	Model model = Model("D:/Programming/CG/small-software-rasterizer/small-software-rasterizer/small-software-rasterizer/rasterizer/resources/head.obj");
	for (int i = 0; i < model.nfaces(); ++i)
	{
		std::vector<Vec2i> screen_coords(3);
		std::vector<int> faces = model.face(i);
		for (int j = 0; j < 3; ++j) 
		{
			Vec3f vertex = model.vert(faces[j]);
			// transfer to screen coord
			screen_coords[j] = Vec2i((vertex.x + 1.0f) * width / 2.0f, (vertex.y + 1.0f) * height / 2.0f);
		}
		Draw::drawTriangle(screen_coords[0], screen_coords[1], screen_coords[2], render.renderImage, TGAColor(rand() % 255, rand() % 255, rand() % 255, 255));
	}
}

void drawHeadLight(Render& render)
{
	// load .obj
	Model model = Model("D:/Programming/CG/small-software-rasterizer/small-software-rasterizer/small-software-rasterizer/rasterizer/resources/head.obj");
	Vec3f light_dir(0, 0, -1); // define light_dir

	for (int i = 0; i < model.nfaces(); i++)
	{
		std::vector<int> face = model.face(i);
		Vec2i screen_coords[3];
		Vec3f world_coords[3];
		for (int j = 0; j < 3; j++)
		{
			Vec3f v = model.vert(face[j]);
			screen_coords[j] = Vec2i((v.x + 1.) * width / 2., (v.y + 1.) * height / 2.);
			world_coords[j] = v;
		}
		// cross product to get normal
		Vec3f n = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);
		n.normalize();
		// dot product
		float intensity = n * light_dir;
		if (intensity > 0)
		{
			Draw::drawTriangle(screen_coords[0], screen_coords[1], screen_coords[2], render.renderImage, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
		}
	}
}

void drawSomeTriangles(Render& render)
{
	Vec2i t0[3] = { Vec2i(10, 10),   Vec2i(100, 30),  Vec2i(190, 160) };
	Draw::drawTriangle(t0[0], t0[1], t0[2], render.renderImage, GREEN);
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