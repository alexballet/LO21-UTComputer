#ifndef QCOMPUTER_H
#define QCOMPUTER_H

#include <QWidget>
#include <QDebug>
#include <QVector>
#include "pile.h"
#include "controleur.h"
#include "options.h"
//#include "computer.h"

namespace Ui {
    class QComputer;
}

class QComputer : public QWidget //changer en QMainWindow? pour utiliser direct QMenuBar
{
    Q_OBJECT

public:
    explicit QComputer(QWidget *parent = 0);
    ~QComputer();
public slots:
    void refresh();
    void on_commande_returnPressed();
    void slotOptions();
private slots:
    void editCommmande();
    void activerClavier(bool);


private:
    Ui::QComputer *ui;
};

#endif // QCOMPUTER_H
