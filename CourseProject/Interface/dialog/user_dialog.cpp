#include "Interface/dialog/user_dialog.h"

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

//Input Dialog Class
QString GraphicsDialog::getSphere() const  { return m_ptxtSphere->text(); }
QString GraphicsDialog::getCylinder() const { return m_ptxtCylinder->text(); }
GraphicsDialog::GraphicsDialog(QWidget *pwgt) : QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    m_ptxtCylinder = std::shared_ptr<QLineEdit>(new QLineEdit);
    m_ptxtSphere = std::shared_ptr<QLineEdit>(new QLineEdit);

    labelSphere = std::shared_ptr<QLabel>(new QLabel("&Сфера: "));
    labelSphere->setBuddy(m_ptxtSphere.get());

    labelCylinder = std::shared_ptr<QLabel>(new QLabel("&Цилиндр"));
    labelCylinder->setBuddy((m_ptxtCylinder.get()));

    btnOk = std::shared_ptr<QPushButton>(new QPushButton("&Ok"));
    connect(btnOk.get(), SIGNAL(clicked()), SLOT(accept()));

    btnCancel = std::shared_ptr<QPushButton>(new QPushButton("&Отмена"));
    connect(btnCancel.get(), SIGNAL(clicked()), SLOT(reject()));

    //Layout setup
    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->addWidget(labelSphere.get(), 0, 0);
    ptopLayout->addWidget(labelCylinder.get(), 1, 0);
    ptopLayout->addWidget(m_ptxtSphere.get(), 0, 1);
    ptopLayout->addWidget(m_ptxtCylinder.get(), 1, 1);
    ptopLayout->addWidget(btnOk.get(), 2,0);
    ptopLayout->addWidget(btnCancel.get(), 2, 1);
    setLayout(ptopLayout);
}

/*
UserDialog::UserDialog() { this->dialog = new InputDialog; }
UserDialog::~UserDialog() { delete this->dialog; }


AskGraphics::AskGraphics() { this->dialog = new InputDialog; }
AskGraphics::~AskGraphics() { delete this->dialog; }
void AskGraphics::exec()
{
    if (dialog->exec() == QDialog::Accepted) {
        QMessageBox::information(0,
                                 "Information",
                                 "Sphere: "
                                 + dialog->getSphere()
                                 + "\nCylinder: "
                                 + dialog->getCylinder()
                                );
    }
}
*/
