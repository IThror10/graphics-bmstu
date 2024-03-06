#ifndef PAINTERIMP_H
#define PAINTERIMP_H

#include <iostream>
#include "Core/rgbColor.h"

class BaseCanvas;
class FlatCoords;

class PainterImp
{
public:
    virtual void draw_line(BaseCanvas& image, const FlatCoords& point1, const FlatCoords& point2, int width) = 0;
    virtual void draw_text(BaseCanvas& image, const FlatCoords& point, int height, const std::string& text) = 0;
    virtual void draw_selected(BaseCanvas& image, const FlatCoords& point1, const FlatCoords& point2, int width) = 0;
    virtual void draw_circle(BaseCanvas& image, const FlatCoords& point1, int radius) = 0;
    virtual void setColor(const RGBColor& color) = 0;
    virtual void setBackground(const RGBColor& color) = 0;
};
#endif // PAINTERIMP_H
