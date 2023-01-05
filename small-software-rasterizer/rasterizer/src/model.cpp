#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char* filename) : verts_(), faces_() , coords_(), coordsId_(), normalsId_()
{
	std::ifstream in;
	std::cout << "Start loading model from: " << filename << std::endl;
	in.open(filename, std::ifstream::in);
	//if (in.fail()) 
	//	std::cout << "Loading model failed" << std::endl;
	//	return;
	std::string line;
	while (!in.eof())
	{
		std::getline(in, line);
		//std::cout << "Loading line " << line << std::endl;
		std::istringstream iss(line.c_str());
		char trash;
		if (!line.compare(0, 2, "v "))
		{
			iss >> trash;
			vec3f v;
			for (int i = 0; i < 3; i++) iss >> v[i];
			verts_.push_back(v);
		}
		else if (!line.compare(0, 2, "f "))
		{
			std::vector<int> f;
			std::vector<int> uvi;
			std::vector<int> normali;
			int uvid, idx, nid;
			iss >> trash;
			while (iss >> idx >> trash >> uvid >> trash >> nid)
			{
				//std::cout << "vertex id: " << idx << std::endl;
				//std::cout << "uv id: " << uvid << std::endl;
				//std::cout << "normal id: " << nid << std::endl;
				idx--; // in wavefront obj all indices start at 1, not zero
				uvid--;
				nid--;
				f.push_back(idx);
				uvi.push_back(uvid);
				normali.push_back(nid);
			}
			
			faces_.push_back(f);
			coordsId_.push_back(uvi);
			normalsId_.push_back(normali);
		}
		else if (!line.compare(0, 3, "vt "))
		{
			iss >> trash >> trash;
			vec2f vt;
			for (int i = 0; i < 2; i++) 
				iss >> vt[i];
			coords_.push_back(vt);
		}
		else if (!line.compare(0, 3, "vn "))
		{
			iss >> trash >> trash;
			vec3f n;
			for (int i = 0; i < 3; i++)
				iss >> n[i];
			normals_.push_back(n);
		}
	}
	std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << std::endl;
}

Model::~Model()
{
}

int Model::nverts()
{
	return (int)verts_.size();
}

int Model::nfaces()
{
	return (int)faces_.size();
}

std::vector<int> Model::face(int idx)
{
	return faces_[idx];
}

vec3f Model::vert(int i)
{
	return verts_[i];
}

std::vector<int> Model::coordsId(int idx)
{
	return coordsId_[idx];
}

vec2f Model::coords(int uvid)
{
	return coords_[uvid];
}

vec3f Model::normal(int id)
{
	return normals_[id];
}

std::vector<int> Model::normalId(int idx)
{
	return normalsId_[idx];
}
