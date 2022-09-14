#include <tgaimage.h>
#include <draw.h>
#include <render.h>
#include <model.h>

const TGAColor WHITE = TGAColor(255, 255, 255, 255);
const TGAColor RED = TGAColor(255, 0, 0, 255);
const int width = 800;
const int height = 800;

int main() {
	Render render = Render(width, height, TGAImage::RGB);

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
			Draw::drawLine(x0, y0, x1, y1, render.renderImage, WHITE);
		}
	}

	render.renderImage.flip_vertically();
	render.renderImage.write_tga_file("output.tga");
	return 0;
}