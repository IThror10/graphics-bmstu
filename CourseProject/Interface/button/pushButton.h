#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QWidget>
#include <iostream>

#include "Core/flatCoords.h"

class PushButton
{
public:
    PushButton();
    virtual void initialize(void *parent, const char *name) = 0;
    virtual void setPosition(const FlatCoords& position, const FlatCoords& size) = 0;
    virtual void setIcon(const std::string& path, const FlatCoords& iconSize) = 0;
    virtual bool clicked() = 0;
    virtual bool released() = 0;
    const void* getButton() const;

protected:
    bool _clicked;
    void *button;
};
#endif // PUSHBUTTON_H
