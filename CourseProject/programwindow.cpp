#include "programwindow.h"
#include "./ui_programwindow.h"

#include "Interface/dialog/user_dialog.h"
#include "builder/springBuilder.h"
#include "model/command_main.h"
#include "mediator/spaceCanvasMediator.h"

ProgramWindow::ProgramWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::ProgramWindow)
{
    ui->setupUi(this);
    scene = new BaseScene(ui->centralwidget, FlatCoords(0, 0));
    canvas = new QtCanvas(ui->centralwidget, FlatCoords(870, 10), FlatCoords(751, 751));
    canvas->setMediator(std::shared_ptr<CanvasMediator>(new SpaceCanvasMediator(this)));

    draw_command.task = to_draw_scene;
    draw_command.params.canvas.scene = canvas->scene;
    draw_command.params.canvas.label = ui->lineEdit_3;

    settings.fill_type = not_set;
    settings.sphere_faces = 10;
    settings.cylinder_faces = 10;
    this->on_settings_fill_phong_triggered();
}

ProgramWindow::~ProgramWindow()
{
    delete ui;
}


void ProgramWindow::on_settings_poly_triggered()
{
    GraphicsDialog dialog(nullptr);
    dialog.setMinimumSize(200, 200);
    if (dialog.exec() == QDialog::Accepted)
    {
        bool success;
        int sphere, cylinder;

        sphere = dialog.getSphere().toDouble(&success);
        if (success)
            cylinder = dialog.getCylinder().toDouble(&success);

        if (success && sphere >= 3 && cylinder >= 4)
        {
            this->settings.sphere_faces = sphere;
            this->settings.cylinder_faces = cylinder;
            QMessageBox::information(0, "Настройки графики", "Данные натройки будут применены при построении следующей модели");
        }
        else
            QMessageBox::warning(0, "Graphic settings", "Wrong faces amount");
    }
}

void ProgramWindow::on_settings_fill_phong_triggered()
{
    if (settings.fill_type != flat)
    {
        ui->settings_fill_gouraud->setCheckable(false);
        ui->settings_fill_gouraud->setEnabled(true);
        ui->settings_fill_mono->setCheckable(false);
        ui->settings_fill_mono->setEnabled(true);

        ui->settings_fill_phong->setCheckable(true);
        ui->settings_fill_phong->setChecked(true);
        ui->settings_fill_phong->setEnabled(false);
        settings.fill_type = flat;
    }
}


void ProgramWindow::on_settings_fill_gouraud_triggered()
{
    QMessageBox::warning(0, "Закраска Гуро", "Данная закраска недоступна");
            return ;
    if (settings.fill_type != gouraud)
    {
        ui->settings_fill_phong->setCheckable(false);
        ui->settings_fill_phong->setEnabled(true);
        ui->settings_fill_mono->setCheckable(false);
        ui->settings_fill_mono->setEnabled(true);

        ui->settings_fill_gouraud->setCheckable(true);
        ui->settings_fill_gouraud->setChecked(true);
        ui->settings_fill_gouraud->setEnabled(false);
        settings.fill_type = gouraud;
    }
}


void ProgramWindow::on_settings_fill_mono_triggered()
{
    if (settings.fill_type != mono)
    {
        ui->settings_fill_phong->setCheckable(false);
        ui->settings_fill_phong->setEnabled(true);
        ui->settings_fill_gouraud->setCheckable(false);
        ui->settings_fill_gouraud->setEnabled(true);

        ui->settings_fill_mono->setCheckable(true);
        ui->settings_fill_mono->setChecked(true);
        ui->settings_fill_mono->setEnabled(false);
        settings.fill_type = mono;
    }
}

void ProgramWindow::on_pushButton_clicked()
{
    command instruction;
    instruction.task = to_set_settings;
    instruction.params.settings = settings;
    complete_command(instruction);

    std::shared_ptr<SpringBuilder> builder(new SpringBuilder);
    if (scene->createModel(builder))
    {
        instruction.task = to_create_model;
        instruction.params.model = builder->createModel();
        complete_command(instruction);
        builder->delete_model();
        complete_command(draw_command);
    }
}

