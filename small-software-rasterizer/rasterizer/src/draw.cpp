#include <draw.h>

void Draw::drawLine(int startX, int startY, int endX, int endY, TGAImage& image, const TGAColor& color)
{
    bool steep = false;
    if (std::abs(startX - endX) < std::abs(startY - endY)) {
        std::swap(startX, startY);
        std::swap(endX, endY);
        steep = true;
    }
    if (startX > endX) {
        std::swap(startX, endX);
        std::swap(startY, endY);
    }

    for (int x = startX; x <= endX; ++x) {
        float t = (x - startX) / (float)(endX - startX);
        int y = startY * (1.0f - t) + endY * t;
        if (steep) {
            image.set(y, x, color);
        }
        else {
            image.set(x, y, color);
        }
    }
}
