#ifndef USER_DIALOG_H
#define USER_DIALOG_H

#include <QMessageBox>
#include <iostream>

#include <QDialog>
#include <QLineEdit>
#include <memory>

class GraphicsDialog : public QDialog
{
    Q_OBJECT
public:
    GraphicsDialog(QWidget* pwgt = 0);
    QString getSphere() const;
    QString getCylinder() const;

private:
    std::shared_ptr<QLineEdit> m_ptxtSphere;
    std::shared_ptr<QLineEdit> m_ptxtCylinder;

    std::shared_ptr<QLabel> labelSphere;
    std::shared_ptr<QLabel> labelCylinder;

    std::shared_ptr<QPushButton> btnOk;
    std::shared_ptr<QPushButton> btnCancel;
};


#endif // USER_DIALOG_H

