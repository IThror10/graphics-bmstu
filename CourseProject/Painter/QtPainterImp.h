#ifndef QTPAINTERIMP_H
#define QTPAINTERIMP_H

#include "Painter/PainterImp.h"
#include <QColor>

class QtPainterImp: public PainterImp
{
public:
    virtual void draw_line(BaseCanvas& image, const FlatCoords& point1, const FlatCoords& point2, int width) override;
    virtual void draw_text(BaseCanvas& image, const FlatCoords& point, int height, const std::string& text) override;
    virtual void draw_selected(BaseCanvas& image, const FlatCoords& point1, const FlatCoords& point2, int width) override;
    virtual void draw_circle(BaseCanvas& image, const FlatCoords& center, int radius) override;
    virtual void setColor(const RGBColor& color) override;
    virtual void setBackground(const RGBColor& color) override;
protected:
    QColor color;
    QColor fond;
};

#endif // QTPAINTERIMP_H
