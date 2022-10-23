#pragma once
#include <vector>
#include <geometry.h>

class Model {
public:
	Model(const char* filename);
	~Model();
	int nverts();
	int nfaces();
	vec3f vert(int i);
	std::vector<int> face(int idx);


	vec2f coords(int uvid);
	std::vector<int> coordsId(int idx);

	vec3f normal(int id);
	std::vector<int> normalId(int idx);

private:
	std::vector<vec3f> verts_;
	std::vector<std::vector<int>> faces_;

	std::vector<vec2f> coords_;
	std::vector<std::vector<int>> coordsId_;

	std::vector<vec3f> normals_;
	std::vector<std::vector<int>> normalsId_;
};