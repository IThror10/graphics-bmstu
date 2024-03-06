#include "Interface/abstractFactory.h"
#include "Interface/QtFactory.h"

Factory AbstractFactory::_instance = Factory(nullptr);

Factory AbstractFactory::Instance()
{
    if (_instance == nullptr)
    {
        _instance = Factory(new QtFactory);
    }
    return _instance;
}
