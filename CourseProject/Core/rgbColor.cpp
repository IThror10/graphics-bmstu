#include "Core/rgbColor.h"

RGBColor::RGBColor()
    : r(128), g(128), b(128), alpha(128) {}

RGBColor::RGBColor(int _r, int _g, int _b, int _alpha)
    : r(_r), g(_g), b(_b), alpha(_alpha) {}

void RGBColor::setRGB(int _r, int _g, int _b, int _alpha)
{
    r = _r;
    g = _g;
    b = _b;
    alpha = _alpha;
}

RGBColor& RGBColor::operator=(const RGBColor& color)
{
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
    this->alpha = color.alpha;
    return *this;
}
