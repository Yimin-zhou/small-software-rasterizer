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

void Draw::drawTriangle(Vec2i v0, Vec2i v1, Vec2i v2, TGAImage& image, const TGAColor& color)
{
    drawLine(v0, v1, image, color);
    drawLine(v1, v2, image, color);
    drawLine(v2, v0, image, color);

    // how to fill triangles
    // Sort vertices of the triangle by their y-coordinates;
    //Rasterize simultaneously the leftand the right sides of the triangle;
    //Draw a horizontal line segment between the leftand the right boundary points.


}
