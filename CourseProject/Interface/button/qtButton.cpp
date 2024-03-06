#include "Interface/button/qtButton.h"
#include <QString>

QtButton::QtButton()
{
    this->specButton = new QPushButton(nullptr);
    this->button = (void*)this->specButton;
}

void QtButton::initialize(void *parent, const char *name)
{
    this->specButton->setParent((QWidget*)parent);
    this->specButton->setObjectName(QString::fromUtf8(name));
    this->specButton->setText(QString());
}


void QtButton::setPosition(const FlatCoords& position, const FlatCoords& size)
{
    this->specButton->setGeometry(position.x, position.y, size.x, size.y);
}


void QtButton::setIcon(const std::string& path, const FlatCoords& size)
{
    this->specButton->setIcon(QIcon(QString(path.c_str())));
    this->specButton->setIconSize(QSize(size.x, size.y));
}

bool QtButton::clicked()
{
    if (_clicked == false)
    {
        this->_clicked = true;
        this->specButton->setStyleSheet("QPushButton{"
           "background-color: rgb(255, 130, 00);}");
        return true;
    }
    return false;
}

bool QtButton::released()
{
    if (_clicked)
    {
        _clicked = false;
        this->specButton->setStyleSheet("QPushButton{"
                "background-color: rgb(225, 225, 225);}");
        return true;
    }
    return false;
}
