#ifndef QTCANVASMENU_H
#define QTCANVASMENU_H

#include "Interface/menu/canvasMenu.h"

class QtCanvasMenu: public CanvasMenu, public QWidget
{
public:
    QtCanvasMenu(BaseScene *scene, void *parent, const FlatCoords& position);

private slots:
    void on_single_line_clicked();
    void on_double_line_clicked();
    void on_tripple_line_clicked();

    void on_triangle_clicked();
    void on_square_clicked();
    void on_pentagon_clicked();
    void on_septagon_clicked();
    void on_geksagon_clicked();

    void on_remove_clicked();
    void on_clear_clicked();

    void on_c_elem_clicked();
    void on_h_elem_clicked();
    void on_n_elem_clicked();
    void on_o_elem_clicked();
    void on_s_elem_clicked();
    void on_choose_elem_clicked();
};
#endif // QTCANVASMENU_H
