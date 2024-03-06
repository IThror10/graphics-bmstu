#ifndef CURSOR_H
#define CURSOR_H

#include "Objects/baseObject.h"
#include <memory>

class BaseCursor
{
public:
    BaseCursor();
    float get_x();
    float get_y();
    void set_coords(float x_coord, float y_coord);
    void reset();

protected:
    float x_pos;
    float y_pos;
    std::shared_ptr<BaseObject> selected;
};

#endif // CURSOR_H
