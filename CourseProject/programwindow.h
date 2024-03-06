#ifndef PROGRAMWINDOW_H
#define PROGRAMWINDOW_H

#include <QMainWindow>
#include <Meta/settings.h>
#include "Interface/canvas/qtCanvas.h"
#include "model/command_main.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ProgramWindow; }
QT_END_NAMESPACE

class ProgramWindow : public QMainWindow
{
    Q_OBJECT

public:
    ProgramWindow(QWidget *parent = nullptr);
    ~ProgramWindow();
    command draw_command;

private slots:
    void on_settings_poly_triggered();

    void on_settings_fill_phong_triggered();

    void on_settings_fill_gouraud_triggered();

    void on_settings_fill_mono_triggered();

    void on_pushButton_clicked();

private:
    Ui::ProgramWindow *ui;
    BaseScene *scene;
    QtCanvas *canvas;
    Settings settings;
};

#endif // PROGRAMWINDOW_H
