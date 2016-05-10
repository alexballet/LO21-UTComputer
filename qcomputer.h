#ifndef QCOMPUTER_H
#define QCOMPUTER_H

#include <QWidget>
#include <QDebug>
#include <QVector>
#include "pile.h"
#include "controleur.h"
//#include "computer.h"

namespace Ui {
    class QComputer;
}

class QComputer : public QWidget
{
    Q_OBJECT

public:
    explicit QComputer(QWidget *parent = 0);
    ~QComputer();
public slots:
    void refresh();
private slots:
void on_commande_returnPressed();
void editCommmande();

void on_activerClavier_stateChanged(int arg1);

private:
    Ui::QComputer *ui;
};

#endif // QCOMPUTER_H
