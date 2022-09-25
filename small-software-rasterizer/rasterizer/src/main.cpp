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
		std::vector<int> faces = model.face(i);
		for (int j = 0; j < 3; ++j) {
			Vec3f v0 = model.vert(faces[j]);
			Vec3f v1 = model.vert(faces[(j + 1) % 3]);
			int x0 = (v0.x + 1.0f) * render.renderWidth / 2.0f;
			int y0 = (v0.y + 1.0f) * render.renderHeight / 2.0f;
			int x1 = (v1.x + 1.0f) * render.renderWidth / 2.0f;
			int y1 = (v1.y + 1.0f) * render.renderHeight / 2.0f;
			Draw::drawLine(Vec2i(x0, y0), Vec2i(x1, y1), render.renderImage, WHITE);
		}
	}
}

void drawSomeTriangles(Render& render)
{
	Vec2i t0[3] = { Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80) };
	Vec2i t1[3] = { Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180) };
	Vec2i t2[3] = { Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180) };
	Draw::drawTriangle(t0[0], t0[1], t0[2], render.renderImage, RED);
	Draw::drawTriangle(t1[0], t1[1], t1[2], render.renderImage, WHITE);
	Draw::drawTriangle(t2[0], t2[1], t2[2], render.renderImage, GREEN);
}

int main() {
	// initialize render
	Render render = Render(width, height, TGAImage::RGB);

	//draw something
	drawSomeTriangles(render);

	// output
	render.renderImage.flip_vertically();
	render.renderImage.write_tga_file("output.tga");
	return 0;
}