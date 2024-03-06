#include "Interface/canvas/qtCanvas.h"
#include <QMouseEvent>

QtCanvas::QtCanvas(void *parent, const FlatCoords& coords, const FlatCoords& size)
    : BaseCanvas(parent, coords, size), QGraphicsView((QWidget*)parent)
{
    this->setObjectName(QString::fromUtf8("molview"));
    this->setGeometry(QRect(coords.x, coords.y, size.x, size.y));
    this->setSceneRect(0, 0, size.x - 5, size.y - 5);
    this->setMouseTracking(true);

    scene = new QGraphicsScene(this);
    this->setScene(scene);
    this->scene->addRect(0, 0, size.x - 5, size.y - 5);
}

void QtCanvas::clear()
{
    this->scene->clear();
}

void QtCanvas::mousePressEvent(QMouseEvent*event)
{
    if (mediator)
    {
        QPointF point = event->localPos();
        FlatCoords coords(point.x(), point.y());

        if (event->buttons() & Qt::LeftButton)
            this->mediator->left_clicked(coords);
        else
            this->mediator->right_clicked(coords);
    }
}

void QtCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (mediator)
    {
        QPointF point = event->localPos();
        FlatCoords coords(point.x(), point.y());
        this->mediator->mouse_moved(coords);
    }
}

void QtCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (mediator)
        this->mediator->released();
}

void QtCanvas::wheelEvent(QWheelEvent *event)
{
    if (mediator)
        this->mediator->wheel_event(event->angleDelta().x(), event->angleDelta().y());
}

void QtCanvas::restoreSize()
{
    scene->update(position.x, position.y, mySize.x, mySize.y);
}
