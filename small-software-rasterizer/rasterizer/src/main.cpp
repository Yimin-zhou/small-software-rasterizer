#include <tgaimage.h>
#include <draw.h>
#include <render.h>
#include <model.h>
#include "matrix.h"
#include "shader.h"

const TGAColor WHITE = TGAColor(255, 255, 255, 255);
const TGAColor RED = TGAColor(255, 0, 0, 255);
const TGAColor GREEN = TGAColor(0, 255, 0, 255);
const int width = 800;
const int height = 800;

Model* model = NULL;
vec3f light_dir(0, 0, 1); // define light_dir
vec3f camera(1, 1, 3);
vec3f center(0, 0, 0); // in camera space


vec3f world2screen(vec3f v)
{
	return vec3f(int((v.x + 1.) * width / 2. + .5), int((v.y + 1.) * height / 2. + .5), v.z);
}

// define shaders here for now:
class Shader : public IShader
{
public:
	//vec3f varying_normal; // written by vertex shader, read by fragment shader
	//vec2f varying_uv;        // same as above
	vec4f vertex(int iface, int nthvert, matrix4x4 viewport, matrix4x4 projection, matrix4x4 modelView) override
	{
		varying_uv = model->coords(model->coordsId(iface)[nthvert]);
		varying_normal = model->normal(model->normalId(iface)[nthvert]); // get diffuse lighting intensity
		vec4f vertex; // read the vertex from .obj file
		for (int k = 0; k < 3; k++) vertex[k] = model->vert(model->face(iface)[nthvert])[k];
		vertex[3] = 1;
		return  viewport * projection * modelView * vertex; // transform it to screen coordinates
	}

	bool fragment(vec3f bc, TGAColor& color, TGAImage& texture, vec3f normal, vec2f uv) override
	{
		color = texture.get(uv.x * texture.get_width(), uv.y * texture.get_height()) * std::max(0.f, (normal * light_dir));      // well duh
		/*std::cout << world_normal * light_dir << std::endl;*/
		return false;                              // no, we do not discard this pixel
	}
};

void drawHeadLight(Render& render)
{
	// load .obj
	model = new Model("resources/african_head.obj");
	TGAImage texture = TGAImage();
	texture.read_tga_file("resources/african_head_diffuse.tga");
	texture.flip_vertically();

	matrix4x4 modelView = Matrix::lookAt(camera, center, vec3f(0, 1, 0)); // object to world
	matrix4x4 projection = Matrix::projection(-1.f / (camera - center).norm()); // world to clip space
	matrix4x4 viewPort = Matrix::viewPort(width / 8, height / 8, width * 3 / 4, height * 3 / 4); // clip to screen

	TGAImage zbuffer(width, height, TGAImage::GRAYSCALE);

	// create shader
	Shader shaderTemp;

	for (int i = 0; i < model->nfaces(); i++)
	{
		vec4f screen_coords[3];
		std::vector<int> uvids = model->coordsId(i);
		std::vector<int> nids = model->normalId(i);
		vec2f uvs[3];
		vec3f normals[3];

		for (int j = 0; j < 3; j++)
		{
			screen_coords[j] = shaderTemp.vertex(i, j, viewPort, projection, modelView);
			uvs[j] = model->coords(uvids[j]);
			normals[j] = model->normal(nids[j]);
		}
		
		Draw::drawTriangle(screen_coords, normals, uvs, shaderTemp, render.renderImage, texture, zbuffer);
	}

	zbuffer.flip_vertically();
	zbuffer.write_tga_file("depth.tga");
}

int main() 
{
	// initialize render
	Render render = Render(width, height, TGAImage::RGB);

	//draw something
	drawHeadLight(render);

	// output
	render.renderImage.flip_vertically();
	render.renderImage.write_tga_file("output.tga");
	return 0;
}