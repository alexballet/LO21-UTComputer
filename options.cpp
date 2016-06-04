#include "options.h"
#include "ui_options.h"
#include <QSettings>

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);

    //connecting radioButtons and dial
    connect(ui->activerClavier, SIGNAL(toggled(bool)), this, SLOT(activerClavierOpt(bool)));
    connect(ui->activerBip, SIGNAL(toggled(bool)), this, SLOT(activerBipOpt(bool)));
    connect(ui->dial, SIGNAL(valueChanged(int)), this, SLOT(setMaxAfficheSlot(int)));

    //getting settings values
    QSettings settings;
    ui->activerClavier->setChecked(settings.value("Clavier").toBool());
    ui->activerBip->setChecked(settings.value("Bip").toBool());
    ui->dial->setValue(settings.value("Pile").toInt());
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

void Options::setMaxAfficheSlot(int i) {
    QSettings settings;
    settings.setValue("Pile", i);
    emit setMaxAfficheSig(i);
}

 void Options::activerBipOpt(bool s){
     QSettings settings;
     settings.setValue("Bip", s);
 }
