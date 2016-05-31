#include "restorecontextwindow.h"
#include "ui_restorecontextwindow.h"

RestoreContextWindow::RestoreContextWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RestoreContextWindow)
{
    ui->setupUi(this);
}

RestoreContextWindow::~RestoreContextWindow()
{
    delete ui;
}
