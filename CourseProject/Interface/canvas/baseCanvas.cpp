#include "Interface/canvas/baseCanvas.h"

BaseCanvas::BaseCanvas(void *_parent, const FlatCoords& coords, const FlatCoords& _size)
    :   parent(_parent), position(coords), mySize(_size) {}

void BaseCanvas::setMediator(std::shared_ptr<CanvasMediator> _mediator)
{
    this->mediator = _mediator;
}
