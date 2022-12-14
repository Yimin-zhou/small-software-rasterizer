#include <draw.h>
#include <helper.h>


//void Draw::drawLine(vec2f v0, vec2f v1, TGAImage& image, const TGAColor& color)
//{
//	bool steep = false;
//	if (std::abs(v0.x - v1.x) < std::abs(v0.y - v1.y))
//	{
//		std::swap(v0.x, v0.y);
//		std::swap(v1.x, v1.y);
//		steep = true;
//	}
//	if (v0.x > v1.x)
//	{
//		std::swap(v0.x, v1.x);
//		std::swap(v0.y, v1.y);
//	}
//
//	for (int x = v0.x; x <= v1.x; ++x) {
//		float t = (x - v0.x) / (float)(v1.x - v0.x);
//		int y = v0.y * (1.0f - t) + v1.y * t;
//		if (steep) {
//			image.set(y, x, color);
//		}
//		else {
//			image.set(x, y, color);
//		}
//	}
//}
//
//void Draw::drawTriangleSweeping(vec2f v0, vec2f v1, vec2f v2, TGAImage& image, const TGAColor& color)
//{
//    // method 1 sweeping
//    // how to fill triangles
//    // 1.Sort vertices of the triangle by their y-coordinates;
//    // 2.Rasterize simultaneously the leftand the right sides of the triangle;
//    // 3.Draw a horizontal line segment between the leftand the right boundary points.
//
//    // sort triangles base on y, from high to low
//    if (v0.y > v1.y) std::swap(v0, v1);
//    if (v0.y > v2.y) std::swap(v0, v2);
//    if (v1.y > v2.y) std::swap(v1, v2);
//
//    float totalHeight = v2.y - v0.y;
//    // draw lower part
//    for (int y = v0.y; y <= v1.y; ++y)
//    {
//        float segmentHeight = v1.y - v0.y + 1.0f;
//        float a = (float)(y - v0.y) / segmentHeight;
//        float b = (float)(y - v0.y) / totalHeight;
//        int x1 = (1.0f - a) * v0.x + v1.x * a;
//        int x2 = (1.0f - b) * v0.x + v2.x * b;
//        // draw horizontal line
//        if (x1 > x2) std::swap(x1, x2);
//        for (int x = x1; x <= x2; ++x)
//        {
//            image.set(x, y, color);
//        }
//    }
//    // draw upper part
//    for (int y = v1.y; y <= v2.y; ++y)
//    {
//        float segmentHeight = v2.y - v1.y + 1.0f;
//        float a = (float)(y - v1.y) / segmentHeight;
//        float b = (float)(y - v0.y) / totalHeight;
//        int x1 = (1.0f - a) * v1.x + v2.x * a;
//        int x2 = (1.0f - b) * v0.x + v2.x * b;
//        // draw horizontal line
//        if (x1 > x2) std::swap(x1, x2);
//        for (int x = x1; x <= x2; ++x)
//        {
//            image.set(x, y, color);
//        }
//    }
//}

// 3D model
void Draw::drawTriangle(vec4f* pts, vec3f* normals, vec2f* uvs ,IShader& shader, TGAImage& image, TGAImage& texture, TGAImage& zBuffer)
{
	// checking if a poin is in triangle/bounding box
	// 0 = P(barycenter)A + uAB + vAC // position of the point
	// https://www.youtube.com/watch?v=HYAgJN3x4GA&ab_channel=SebastianLague

	vec2f bboxmin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	vec2f bboxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			bboxmin[j] = std::min(bboxmin[j], pts[i][j] / pts[i][3]);
			bboxmax[j] = std::max(bboxmax[j], pts[i][j] / pts[i][3]);
		}
	}
	// step2 go through all the points in the box, determine if a point is inside the triangle and fill in the color
	vec3i P;
	TGAColor color;
	for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++)
	{
		for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++)
		{
			vec3f bc_screen = barycentric(proj<2>(pts[0] / pts[0][3]), proj<2>(pts[1] / pts[1][3]), proj<2>(pts[2] / pts[2][3]), proj<2>(P));

            // interpolated depth
			float z = pts[0][2] * bc_screen.x + pts[1][2] * bc_screen.y + pts[2][2] * bc_screen.z;
			float w = pts[0][3] * bc_screen.x + pts[1][3] * bc_screen.y + pts[2][3] * bc_screen.z;
            int frag_depth = std::max(0, std::min(255, int(z / w + .5)));

			if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0 || zBuffer.get(P.x, P.y)[0] > frag_depth) continue;
			P.z = frag_depth;

			vec2f uv;
			vec3f n;
			for (int i = 0; i < 3; i++)
			{
				// calculate interpolated depth
				P.z += pts[i][2] * bc_screen[i];

				// calculate interpolated uv
				uv.x += uvs[i][0] * bc_screen[i];
				uv.y += uvs[i][1] * bc_screen[i];

				// calculate interpolated normal 
				n.x += normals[i][0] * bc_screen[i];
				n.y += normals[i][1] * bc_screen[i];
				n.z += normals[i][2] * bc_screen[i];
			}
			n = n.normalize();

			bool discard = shader.fragment(bc_screen, color, texture, n, uv);
			if (!discard) 
			{
				zBuffer.set(P.x, P.y, TGAColor(frag_depth));
				image.set(P.x, P.y, color);
			}
		}
	}
}
