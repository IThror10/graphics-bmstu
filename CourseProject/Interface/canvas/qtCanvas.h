#ifndef QTCANVAS_H
#define QTCANVAS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "Interface/canvas/baseCanvas.h"

class QtCanvas: public BaseCanvas, public QGraphicsView
{
public:
    QtCanvas(void *parent, const FlatCoords& coords, const FlatCoords& size);
    virtual void clear() override;
    virtual void restoreSize() override;
    QGraphicsScene *scene;

protected:
    virtual void mousePressEvent(QMouseEvent*event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
};

#endif // QTCANVAS_H
