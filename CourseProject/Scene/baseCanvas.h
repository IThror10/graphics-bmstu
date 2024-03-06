#ifndef BASECANVAS_H
#define BASECANVAS_H

#include "Core/flatCoords.h"
#include <memory>
#include <vector>

class CanvasMenu;
class BaseObject;
class BaseImage;

class BaseCanvas
{
public:
    explicit BaseCanvas(const FlatCoords&);
    std::vector<BaseObject>::iterator begin();
    std::shared_ptr<>
    const FlatCoords position;
    const int width;
    const int height;

private:
    std::shared_ptr<BaseObject> composit;
    std::shared_ptr<CanvasMenu> menu;
    std::shared_ptr<BaseImage> image;
};

#endif // BASECANVAS_H
