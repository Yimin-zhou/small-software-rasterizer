#include <draw.h>
#include <helper.h>


void Draw::drawLine(Vec2i v0, Vec2i v1, TGAImage& image, const TGAColor& color)
{
    bool steep = false;
    if (std::abs(v0.x - v1.x) < std::abs(v0.y - v1.y)) {
        std::swap(v0.x, v0.y);
        std::swap(v1.x, v1.y);
        steep = true;
    }
    if (v0.x > v1.x) {
        std::swap(v0.x, v1.x);
        std::swap(v0.y, v1.y);
    }

    for (int x = v0.x; x <= v1.x; ++x) {
        float t = (x - v0.x) / (float)(v1.x - v0.x);
        int y = v0.y * (1.0f - t) + v1.y * t;
        if (steep) {
            image.set(y, x, color);
        }
        else {
            image.set(x, y, color);
        }
    }
}

void Draw::drawTriangleSweeping(Vec2i v0, Vec2i v1, Vec2i v2, TGAImage& image, const TGAColor& color)
{
    // method 1 sweeping
    // how to fill triangles
    // 1.Sort vertices of the triangle by their y-coordinates;
    // 2.Rasterize simultaneously the leftand the right sides of the triangle;
    // 3.Draw a horizontal line segment between the leftand the right boundary points.

    // sort triangles base on y, from high to low
    if (v0.y > v1.y) std::swap(v0, v1);
    if (v0.y > v2.y) std::swap(v0, v2);
    if (v1.y > v2.y) std::swap(v1, v2);

    float totalHeight = v2.y - v0.y;
    // draw lower part
    for (int y = v0.y; y <= v1.y; ++y)
    {
        float segmentHeight = v1.y - v0.y + 1.0f;
        float a = (float)(y - v0.y) / segmentHeight;
        float b = (float)(y - v0.y) / totalHeight;
        int x1 = (1.0f - a) * v0.x + v1.x * a;
        int x2 = (1.0f - b) * v0.x + v2.x * b;
        // draw horizontal line
        if (x1 > x2) std::swap(x1, x2);
        for (int x = x1; x <= x2; ++x)
        {
            image.set(x, y, color);
        }
    }
    // draw upper part
    for (int y = v1.y; y <= v2.y; ++y)
    {
        float segmentHeight = v2.y - v1.y + 1.0f;
        float a = (float)(y - v1.y) / segmentHeight;
        float b = (float)(y - v0.y) / totalHeight;
        int x1 = (1.0f - a) * v1.x + v2.x * a;
        int x2 = (1.0f - b) * v0.x + v2.x * b;
        // draw horizontal line
        if (x1 > x2) std::swap(x1, x2);
        for (int x = x1; x <= x2; ++x)
        {
            image.set(x, y, color);
        }
    }
}

Vec3f Draw::barycentric(std::vector<Vec2i> vertecies, Vec2i p)
{  
    // cross product
    Vec3f u = Vec3f(vertecies[2].x - vertecies[0].x, vertecies[1].x - vertecies[0].x, vertecies[0].x - p.x)
        ^ Vec3f(vertecies[2].y - vertecies[0].y, vertecies[1].y - vertecies[0].y, vertecies[0].y - p.y);
    /* `pts` and `P` has integer value as coordinates
       so `abs(u[2])` < 1 means `u[2]` is 0, that means
       triangle is degenerate, in this case return something with negative coordinates */
    if (std::abs(u.z) < 1) return Vec3f(-1, 1, 1);
    return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}

void Draw::drawTriangle(Vec2i v0, Vec2i v1, Vec2i v2, TGAImage& image, const TGAColor& color)
{
    // checking if a poin is in triangle/bounding box
    // 0 = P(barycenter)A + uAB + vAC // position of the point
    // https://www.youtube.com/watch?v=HYAgJN3x4GA&ab_channel=SebastianLague

    std::vector<Vec2i> vertices = { v0, v1, v2 };
    // step1 form bounding box
    Vec2i bboxMin;
    Vec2i bboxMax;
    Vec2i imageBB = Vec2i(image.get_width() - 1, image.get_height() - 1);
    for (int i = 0; i < 3; ++i)
    {
        bboxMin.x = std::max(0, std::min(vertices[i].x, bboxMin.x));
        bboxMin.y = std::max(0, std::min(vertices[i].y, bboxMin.y));

        bboxMax.x = std::min(imageBB.x, std::max(vertices[i].x, bboxMax.x));
        bboxMax.y = std::min(imageBB.y, std::max(vertices[i].y, bboxMax.y));
    }
    // step2 go through all the points in the box, determine if a point is inside the triangle and fill in the color
    Vec2i p;
    for (p.x = bboxMin.x; p.x <= bboxMax.x; ++p.x)
    {
        for (p.y = bboxMin.y; p.y <= bboxMax.y; ++p.y)
        {
            Vec3f weights = Draw::barycentric(vertices, p);
            if (weights.x < 0 || weights.y < 0 || weights.z < 0) continue;
            else
            {
                image.set(p.x, p.y, color);
            }
        }
    }
}
