#pragma once
#include "geometry.h"

namespace Matrix
{
	inline matrix4x4 lookAt(vec3f camera, vec3f center, vec3f cameraUp);
	inline matrix4x4 viewPort(int x, int y, int w, int h);
	inline matrix4x4 projection(float coeff);

};

// centerPos is a point in camera space (basis)
inline matrix4x4 Matrix::lookAt(vec3f cameraPos, vec3f centerPos, vec3f cameraUp)
{
	vec3f zAxis = (cameraPos - centerPos).normalize();
	vec3f xAxis = cross(cameraUp, zAxis).normalize();
	vec3f yAxis = cross(zAxis, xAxis).normalize();
	matrix4x4 res = matrix4x4::identity();
	for (int i = 0; i < 3; i++)
	{
		res[0][i] = xAxis[i];
		res[1][i] = yAxis[i];
		res[2][i] = zAxis[i];
		res[i][3] = -centerPos[i]; // translate center to cameraPos
	}
	return res;
}

inline matrix4x4 Matrix::projection(float coeff)
{
	matrix4x4 reslult = matrix4x4::identity();
	reslult[3][2] = coeff;
	return reslult;
}

inline matrix4x4 Matrix::viewPort(int x, int y, int w, int h)
{
	// map square [-1,1]*[-1,1]*[-1,1] to image [x,x+w]*[y,y+h]*[0,d]
	matrix4x4 m = matrix4x4::identity();
	m[0][0] = w / 2.f;
	m[0][3] = x + (w / 2.f);
	m[1][1] = h / 2.f;
	m[1][3] = y + (h / 2.f);
	m[2][2] = 255.f / 2.f;
	m[2][3] = 255.f / 2.f;
	m[3][3] = 1;
	return m;
}
