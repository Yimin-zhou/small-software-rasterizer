#include <draw.h>

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

void Draw::drawTriangle(Vec2i v0, Vec2i v1, Vec2i v2, TGAImage& image, const TGAColor& color)
{
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
