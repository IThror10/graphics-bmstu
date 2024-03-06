#include "Painter/QtPainterImp.h"
#include "Interface/canvas/qtCanvas.h"
#include <QGraphicsTextItem>
#include <QDebug>

void QtPainterImp::draw_line(BaseCanvas& image, const FlatCoords& point1, const FlatCoords& point2, int width)
{
    QtCanvas &canvas = dynamic_cast<QtCanvas&>(image);
    QGraphicsScene *scene = canvas.scene;

    QPen pen(this->color, width);
    scene->addLine(point1.x, point1.y, point2.x, point2.y, pen);
}

void QtPainterImp::draw_text(BaseCanvas& image, const FlatCoords& point, int height, const std::string& text)
{
    QtCanvas &canvas = dynamic_cast<QtCanvas&>(image);
    QGraphicsScene *scene = canvas.scene;

    QFont font("Georgia", height / 1.5);
    QGraphicsTextItem *item = scene->addText(QString(text.c_str()), font);
    item->setPos(point.x - height / 1.75, point.y - height / 1.25);
}

void QtPainterImp::draw_selected(BaseCanvas& image, const FlatCoords& point1, const FlatCoords& point2, int width)
{
    QtCanvas &canvas = dynamic_cast<QtCanvas&>(image);
    QGraphicsScene *scene = canvas.scene;

    QPen pen(this->fond);
    QBrush brush(this->fond);

    FlatCoords normal = point1.normal(point2);
    normal = normal.createVector(width * 2);

    QVector<QPoint> points(4);
    points[0].setX(point1.x + normal.x); points[0].setY(point1.y + normal.y);
    points[1].setX(point2.x + normal.x); points[1].setY(point2.y + normal.y);
    points[2].setX(point2.x - normal.x); points[2].setY(point2.y - normal.y);
    points[3].setX(point1.x - normal.x); points[3].setY(point1.y - normal.y);

    scene->addPolygon(QPolygon(points), pen, brush);
}

void QtPainterImp::draw_circle(BaseCanvas& image, const FlatCoords& center, int radius)
{
    QtCanvas &canvas = dynamic_cast<QtCanvas&>(image);
    QGraphicsScene *scene = canvas.scene;

    QPen pen(this->color, 2);
    QBrush brush(this->fond);
    scene->addEllipse(center.x - radius, center.y - radius, 2 * radius, 2 * radius, pen, brush);
}

void QtPainterImp::setColor(const RGBColor& color)
{
    this->color = QColor(color.r, color.g, color.b, color.alpha);
}

void QtPainterImp::setBackground(const RGBColor& color)
{
    this->fond = QColor(color.r, color.g, color.b, color.alpha);
}
