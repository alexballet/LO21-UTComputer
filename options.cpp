#include "options.h"
#include "ui_options.h"
#include <QSettings>

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{

    ui->setupUi(this);
    connect(ui->activerClavier, SIGNAL(toggled(bool)), this, SLOT(activerClavierOpt(bool)));
    QSettings settings;
    //settings.setValue("Clavier", false);
    ui->activerClavier->setChecked(settings.value("Clavier").toBool());
}

Options::~Options()
{
    delete ui;
}

void Options::activerClavierOpt(bool s) {
    QSettings settings;
    settings.setValue("Clavier", s);
    emit activerClavierSig(s);
}
