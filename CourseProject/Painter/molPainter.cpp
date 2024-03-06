#include "Painter/molPainter.h"
#include "Objects/atomObject.h"
#include "Objects/lineObject.h"

#include "Painter/PainterImp.h"
#include "Interface/canvas/baseCanvas.h"


molPainter::molPainter(std::shared_ptr<PainterImp> implementation)
    : imp(implementation), selected(160, 240, 190, 255) {}

void molPainter::draw_atom(BaseCanvas& canvas, const AtomObject& atom)
{
    imp->setBackground(RGBColor(255, 255, 255));
    imp->setColor(atom.color);
    if (atom.isSelected)
        imp->setBackground(selected);

    imp->draw_circle(canvas, atom.coords, atom.radius);
    imp->draw_text(canvas, atom.coords, atom.radius, atom.name);
    imp->setBackground(RGBColor(255, 255, 255));
}

void molPainter::draw_line(BaseCanvas& canvas, const LineObject& line)
{
    FlatCoords begin = line.atomStart->coords, end = line.atomEnd->coords;
    if (line.isSelected)
    {
        imp->setBackground(selected);
        imp->draw_selected(canvas, begin, end, line.width);
    }

    FlatCoords center = (begin + end) * 0.5;
    FlatCoords normal = begin.normal(end);
    normal = normal.createVector(3 * line.width);

    if (line.linesCnt == 2)
    {
        begin += normal * 0.5;
        end += normal * 0.5;
        center += normal * 0.5;
    }
    else
    {
        normal *= (line.linesCnt - 1) / 2;
        begin += normal;
        end += normal;
        center += normal;
    }

    for (int i = 0; i < line.linesCnt; i++)
    {
        imp->setColor(line.atomStart->color);
        imp->draw_line(canvas, begin, center, line.width);
        imp->setColor(line.atomEnd->color);
        imp->draw_line(canvas, center, end, line.width);

        begin -= normal;
        end -= normal;
        center -= normal;
    }

}
