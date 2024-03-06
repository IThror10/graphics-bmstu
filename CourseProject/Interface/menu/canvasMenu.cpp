#include "Interface/menu/canvasMenu.h"
#include "Interface/abstractFactory.h"
#include "Objects/lineObject.h"
#include "Objects/compositObject.h"

CanvasMenu::CanvasMenu(BaseScene *_scene, void *_parent, const FlatCoords& coords)
    : scene(_scene)
{
    //Положение и родитель
    this->parent = _parent;
    this->position = coords;

    //____________Создание кнопок меню____________
    FlatCoords iconSize(60, 60), buttonSize(71, 71);
    std::string copydir("C:/msys64/projects/course/CourseProject/icons/");

    //Single line Button
    single_line = AbstractFactory::Instance()->createButton();
    single_line->initialize(parent, "single_line");
    single_line->setPosition(position, buttonSize);
    single_line->setIcon(copydir + "single.jpg", iconSize);

    //Double line Button
    double_line = AbstractFactory::Instance()->createButton();
    double_line->initialize(parent, "double_line");
    double_line->setPosition(position + FlatCoords(70, 0), buttonSize);
    double_line->setIcon(copydir + "double.jpg", iconSize);

    //Tripple line Button
    tripple_line = AbstractFactory::Instance()->createButton();
    tripple_line->initialize(parent, "tripple_line");
    tripple_line->setPosition(position + FlatCoords(140, 0), buttonSize);
    tripple_line->setIcon(copydir + "tripple.jpg", iconSize);

    //Triangle Figure Button
    triangle = AbstractFactory::Instance()->createButton();
    triangle->initialize(parent, "triangle");
    triangle->setPosition(position + FlatCoords(230, 0), buttonSize);
    triangle->setIcon(copydir + "triangle.jpg", iconSize);

    //Square Figure Button
    square = AbstractFactory::Instance()->createButton();
    square->initialize(parent, "square");
    square->setPosition(position + FlatCoords(300, 0), buttonSize);
    square->setIcon(copydir + "square.jpg", iconSize);

    //Pentagon Figure Button
    pentagon = AbstractFactory::Instance()->createButton();
    pentagon->initialize(parent, "pentagon");
    pentagon->setPosition(position + FlatCoords(370, 0), buttonSize);
    pentagon->setIcon(copydir + "pentagon.jpg", iconSize);

    //Geksagon Figure Button
    geksagon = AbstractFactory::Instance()->createButton();
    geksagon->initialize(parent, "geksagon");
    geksagon->setPosition(position + FlatCoords(440, 0), buttonSize);
    geksagon->setIcon(copydir + "geksagon.jpg", iconSize);

    //Septagon Figure Button
    septagon = AbstractFactory::Instance()->createButton();
    septagon->initialize(parent, "septagon");
    septagon->setPosition(position + FlatCoords(510, 0), buttonSize);
    septagon->setIcon(copydir + "septagon.jpg", iconSize);

    //Remove Button
    remove = AbstractFactory::Instance()->createButton();
    remove->initialize(parent, "remove");
    remove->setPosition(position + FlatCoords(600, 0), buttonSize);
    remove->setIcon(copydir + "remove.jpg", iconSize);

    //Clear Button
    clear = AbstractFactory::Instance()->createButton();
    clear->initialize(parent, "clear");
    clear->setPosition(position + FlatCoords(670, 0), buttonSize);
    clear->setIcon(copydir + "clear.jpg", iconSize);

    //C Button
    c_elem = AbstractFactory::Instance()->createButton();
    c_elem->initialize(parent, "c_elem");
    c_elem->setPosition(position + FlatCoords(741, 80), buttonSize);
    c_elem->setIcon(copydir + "c_elem.jpg", iconSize);

    //H Button
    h_elem = AbstractFactory::Instance()->createButton();
    h_elem->initialize(parent, "h_elem");
    h_elem->setPosition(position + FlatCoords(741, 150), buttonSize);
    h_elem->setIcon(copydir + "h_elem.jpg", iconSize);

    //N Button
    n_elem = AbstractFactory::Instance()->createButton();
    n_elem->initialize(parent, "n_elem");
    n_elem->setPosition(position + FlatCoords(741, 220), buttonSize);
    n_elem->setIcon(copydir + "n_elem.jpg", iconSize);

    //O Button
    o_elem = AbstractFactory::Instance()->createButton();
    o_elem->initialize(parent, "o_elem");
    o_elem->setPosition(position + FlatCoords(741, 290), buttonSize);
    o_elem->setIcon(copydir + "o_elem.jpg", iconSize);

    //S Button
    s_elem = AbstractFactory::Instance()->createButton();
    s_elem->initialize(parent, "s_elem");
    s_elem->setPosition(position + FlatCoords(741, 360), buttonSize);
    s_elem->setIcon(copydir + "s_elem.jpg", iconSize);

    //Choose Button
    choose_elem = AbstractFactory::Instance()->createButton();
    choose_elem->initialize(parent, "choose_elem");
    choose_elem->setPosition(position + FlatCoords(741, 430), buttonSize);
    choose_elem->setIcon(copydir + "choose_elem.jpg", iconSize);
}

//ui->translate->setIcon(QIcon(workdir + "2dto3d.jpg"));
//ui->translate->setIconSize(QSize(110, 110));

ObjPtr CanvasMenu::selectedFigure()
{
    if (_activeFigure)
        return _activeFigure->clone();
    return nullptr;
}

std::shared_ptr<AtomObject> CanvasMenu::selectedAtom()
{
    return std::shared_ptr<AtomObject>(new AtomObject(this->_activeAtom));
}
