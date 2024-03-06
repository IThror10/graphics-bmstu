#include "Interface/menu/qtCanvasMenu.h"
#include "Objects/lineObject.h"
#include "strategy/select/selectStrategy.h"
#include <QPushButton>

QtCanvasMenu::QtCanvasMenu(BaseScene *scene, void *parent, const FlatCoords& coords)
    : CanvasMenu(scene, parent, coords), QWidget((QWidget*)parent)
{
    QObject::connect((QPushButton*)single_line->getButton(), &QPushButton::pressed,
                                    this, &QtCanvasMenu::on_single_line_clicked);
    QObject::connect((QPushButton*)double_line->getButton(), &QPushButton::pressed,
                                    this, &QtCanvasMenu::on_double_line_clicked);
    QObject::connect((QPushButton*)tripple_line->getButton(), &QPushButton::pressed,
                                    this, &QtCanvasMenu::on_tripple_line_clicked);

    QObject::connect((QPushButton*)triangle->getButton(), &QPushButton::pressed,
                                    this, &QtCanvasMenu::on_triangle_clicked);
    QObject::connect((QPushButton*)square->getButton(), &QPushButton::pressed,
                                    this, &QtCanvasMenu::on_square_clicked);
    QObject::connect((QPushButton*)pentagon->getButton(), &QPushButton::pressed,
                                    this, &QtCanvasMenu::on_pentagon_clicked);
    QObject::connect((QPushButton*)geksagon->getButton(), &QPushButton::pressed,
                                    this, &QtCanvasMenu::on_geksagon_clicked);
    QObject::connect((QPushButton*)septagon->getButton(), &QPushButton::pressed,
                                    this, &QtCanvasMenu::on_septagon_clicked);

    QObject::connect((QPushButton*)clear->getButton(), &QPushButton::pressed,
                                    this, &QtCanvasMenu::on_clear_clicked);
    QObject::connect((QPushButton*)remove->getButton(), &QPushButton::pressed,
                                    this, &QtCanvasMenu::on_remove_clicked);

    QObject::connect((QPushButton*)c_elem->getButton(), &QPushButton::pressed,
                                    this, &QtCanvasMenu::on_c_elem_clicked);
    QObject::connect((QPushButton*)h_elem->getButton(), &QPushButton::pressed,
                                    this, &QtCanvasMenu::on_h_elem_clicked);
    QObject::connect((QPushButton*)n_elem->getButton(), &QPushButton::pressed,
                                    this, &QtCanvasMenu::on_n_elem_clicked);
    QObject::connect((QPushButton*)o_elem->getButton(), &QPushButton::pressed,
                                    this, &QtCanvasMenu::on_o_elem_clicked);
    QObject::connect((QPushButton*)s_elem->getButton(), &QPushButton::pressed,
                                    this, &QtCanvasMenu::on_s_elem_clicked);
    QObject::connect((QPushButton*)choose_elem->getButton(), &QPushButton::pressed,
                                    this, &QtCanvasMenu::on_choose_elem_clicked);

    //Инициализация начальных возвращаемых значений
    std::string name = "C";
    _activeAtom = AtomObject(FlatCoords(0, 0), name);
    _activeFigure = ObjPtr(new LineObject(_activeAtom, 1));

    //____Активные кнопки____
    activeFigureButton = single_line;
    single_line->clicked();
    scene->setSelectStategy(std::shared_ptr<SelectStrategy>(new SelectAny));

    activeAtomButton = c_elem;
    activeAtomButton->clicked();
}

void QtCanvasMenu::on_single_line_clicked()
{
    if (single_line->clicked())
    {
        activeFigureButton->released();
        activeFigureButton = single_line;

        _activeFigure = ObjPtr(new LineObject(_activeAtom, 1));
        scene->setSelectStategy(std::shared_ptr<SelectStrategy>(new SelectAny));
    }
}
void QtCanvasMenu::on_double_line_clicked()
{
    if (double_line->clicked())
    {
        activeFigureButton->released();
        activeFigureButton = double_line;

        _activeFigure = ObjPtr(new LineObject(_activeAtom, 2));
        scene->setSelectStategy(std::shared_ptr<SelectStrategy>(new SelectAny));
    }
}
void QtCanvasMenu::on_tripple_line_clicked()
{
    if (tripple_line->clicked())
    {
        activeFigureButton->released();
        activeFigureButton = tripple_line;

        _activeFigure = ObjPtr(new LineObject(_activeAtom, 3));
        scene->setSelectStategy(std::shared_ptr<SelectStrategy>(new SelectAny));
    }
}

void QtCanvasMenu::on_triangle_clicked()
{
    if (triangle->clicked())
    {
        activeFigureButton->released();
        activeFigureButton = triangle;


        _activeFigure = CompositObject::createPolygon(3, std::shared_ptr<AtomObject>(new AtomObject(_activeAtom)));
        scene->setSelectStategy(std::shared_ptr<SelectStrategy>(new SelectLine));
    }
}
void QtCanvasMenu::on_square_clicked()
{
    if (square->clicked())
    {
        activeFigureButton->released();
        activeFigureButton = square;

        _activeFigure = CompositObject::createPolygon(4, std::shared_ptr<AtomObject>(new AtomObject(_activeAtom)));
        scene->setSelectStategy(std::shared_ptr<SelectStrategy>(new SelectLine));
    }
}
void QtCanvasMenu::on_pentagon_clicked()
{
    if (pentagon->clicked())
    {
        activeFigureButton->released();
        activeFigureButton = pentagon;

        _activeFigure = CompositObject::createPolygon(5, std::shared_ptr<AtomObject>(new AtomObject(_activeAtom)));
        scene->setSelectStategy(std::shared_ptr<SelectStrategy>(new SelectLine));
    }
}
void QtCanvasMenu::on_geksagon_clicked()
{
    if (geksagon->clicked())
    {
        activeFigureButton->released();
        activeFigureButton = geksagon;

        _activeFigure = CompositObject::createPolygon(6, std::shared_ptr<AtomObject>(new AtomObject(_activeAtom)));
        scene->setSelectStategy(std::shared_ptr<SelectStrategy>(new SelectLine));
    }
}
void QtCanvasMenu::on_septagon_clicked()
{
    if (septagon->clicked())
    {
        activeFigureButton->released();
        activeFigureButton = septagon;

        _activeFigure = CompositObject::createPolygon(7, std::shared_ptr<AtomObject>(new AtomObject(_activeAtom)));
        scene->setSelectStategy(std::shared_ptr<SelectStrategy>(new SelectLine));
    }
}

void QtCanvasMenu::on_remove_clicked()
{
    if (remove->clicked())
    {
        activeFigureButton->released();
        activeFigureButton = remove;

        _activeFigure = nullptr;
        scene->setSelectStategy(std::shared_ptr<SelectStrategy>(new SelectAny));
    }
}

void QtCanvasMenu::on_clear_clicked()
{
    scene->clearScene();
}

void QtCanvasMenu::on_c_elem_clicked()
{
    if (c_elem->clicked())
    {
        activeAtomButton->released();
        activeAtomButton = c_elem;
        this->_activeAtom.name = "C";
        this->_activeAtom.color = RGBColor(128, 128, 128);
    }
}
void QtCanvasMenu::on_h_elem_clicked()
{
    if (h_elem->clicked())
    {
        activeAtomButton->released();
        activeAtomButton = h_elem;
        this->_activeAtom.name = "H";
        this->_activeAtom.color = RGBColor(49, 49, 252);
    }
}
void QtCanvasMenu::on_n_elem_clicked()
{
    if (n_elem->clicked())
    {
        activeAtomButton->released();
        activeAtomButton = n_elem;
        this->_activeAtom.name = "N";
        this->_activeAtom.color = RGBColor(49, 252, 49);
    }
}
void QtCanvasMenu::on_o_elem_clicked()
{
    if (o_elem->clicked())
    {
        activeAtomButton->released();
        activeAtomButton = o_elem;
        this->_activeAtom.name = "O";
        this->_activeAtom.color = RGBColor(255, 0, 0);
    }
}
void QtCanvasMenu::on_s_elem_clicked()
{
    if (s_elem->clicked())
    {
        activeAtomButton->released();
        activeAtomButton = s_elem;
        this->_activeAtom.name = "S";
        this->_activeAtom.color = RGBColor(224, 236, 56);
    }
}
void QtCanvasMenu::on_choose_elem_clicked()
{
    return ;
    if (choose_elem->clicked())
    {
        activeAtomButton->released();
        activeAtomButton = choose_elem;

        //TODO Получение нужного элемента
    }
}
