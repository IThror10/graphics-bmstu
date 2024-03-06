#ifndef MYQOBJECT_H
#define MYQOBJECT_H

#include "Interface/button/pushButton.h"
#include "Interface/menu/canvasMenu.h"

#include <QGraphicsView>
#include <QPushButton>
#include <QMouseEvent>

class QCanvas: public QGraphicsView
{
public:
    explicit QCanvas(QWidget *parent);
    virtual void mousePressEvent(QMouseEvent*event) override;
    virtual ~QCanvas() {}

private:
    CanvasMenu *menu;
};

#endif // MYQOBJECT_H
