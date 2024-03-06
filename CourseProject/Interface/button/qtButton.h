#ifndef QTBUTTON_H
#define QTBUTTON_H

#include <QPushButton>
#include "Interface/button/pushButton.h"

class QtButton: public PushButton
{
public:
    QtButton();

    virtual void initialize(void *parent, const char *name) override;
    virtual void setPosition(const FlatCoords& position, const FlatCoords& size) override;
    virtual void setIcon(const std::string& path, const FlatCoords& size) override;

    virtual bool clicked() override;
    virtual bool released() override;

private:
    QPushButton *specButton;
};

#endif // QTBUTTON_H
