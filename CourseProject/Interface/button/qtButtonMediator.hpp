#ifndef __QTBUTTONMEDIATOR_HPP__
#define __QTBUTTONMEDIATOR_HPP__

#include <QObject>
template <class Menu>
class QtButton;

template <class Menu>
class qtButtonMediator: public QObject
{
public:
    qtButtonMediator(QtButton<Menu> *button);

public slots:
    void on_button_clicked();

private:
    QtButton<Menu> *button;
};

template <class Menu>
qtButtonMediator<Menu>::qtButtonMediator(QtButton<Menu> *_button)
{
    this->button = _button;
}

#include "QDebug"
template <class Menu>
void qtButtonMediator<Menu>::on_button_clicked()
{
    qDebug() << "CLicked";
    this->button->clicked();
}

#endif //__QTBUTTONMEDIATOR_HPP__
