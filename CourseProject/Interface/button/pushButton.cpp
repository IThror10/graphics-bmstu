#include "Interface/button/pushButton.h"

PushButton::PushButton()
{
    this->_clicked = false;
    this->button = nullptr;
}

const void* PushButton::getButton() const
{
    return this->button;
}
