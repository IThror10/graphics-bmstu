#ifndef RGBCOLOR_H
#define RGBCOLOR_H

class RGBColor
{
public:
    RGBColor();
    RGBColor(int r, int g, int b, int alpha = 255);
    void setRGB(int r, int g, int b, int alpha = 255);

    RGBColor(const RGBColor& color) = default;
    RGBColor& operator=(const RGBColor& color);

    int r;
    int g;
    int b;
    int alpha;
};
#endif // RGBCOLOR_H
