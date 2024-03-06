#ifndef MOLPAINTER_H
#define MOLPAINTER_H

#include <memory>
#include "Core/rgbColor.h"

class PainterImp;
class AtomObject;
class LineObject;
class BaseCanvas;

class molPainter
{
public:
    molPainter(std::shared_ptr<PainterImp> implementation);
    void draw_atom(BaseCanvas& canvas, const AtomObject& atom);
    void draw_line(BaseCanvas& canvas, const LineObject& line);
protected:
    std::shared_ptr<PainterImp> imp;
    RGBColor selected;
};

#endif // MOLPAINTER_H
