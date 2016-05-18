#include "options.h"
#include "ui_options.h"

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{

    ui->setupUi(this);
    connect(ui->activerClavier, SIGNAL(toggled(bool)), this, SLOT(activerClavierOpt(bool)));
}

Options::~Options()
{
    delete ui;
}

void Options::activerClavierOpt(bool s) {
    emit activerClavierSig(s);
}
