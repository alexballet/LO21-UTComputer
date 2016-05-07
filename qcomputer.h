#ifndef QCOMPUTER_H
#define QCOMPUTER_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include "computer.h"

namespace Ui {
class QComputer;
}

class QComputer : public QWidget
{
    Q_OBJECT
//    QLineEdit* message;
//    QTableWidget* vuePile;
//    QLineEdit* commande;
//    QVBoxLayout* couche;
    Pile* pile;
    Controleur* controleur;

public:
    explicit QComputer(QWidget *parent = 0);
    ~QComputer();
public slots:
void refresh();
//void getNextCommande();

private slots:
void on_commande_returnPressed();

private:
    Ui::QComputer *ui;
};

#endif // QCOMPUTER_H
