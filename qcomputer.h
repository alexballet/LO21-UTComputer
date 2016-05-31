#ifndef QCOMPUTER_H
#define QCOMPUTER_H

#include <QWidget>
#include <QDebug>
#include <QVector>
#include <QStringList>
#include <QTableView>
#include <QAction>
#include <QTableWidgetItem>
#include <QMenuBar>
#include <QSettings>
#include <QStandardPaths>
#include <QShortcut>
#include "pile.h"
#include "controleur.h"
#include "options.h"
#include "variableeditor.h"
#include "programeditor.h"
#include "restorecontextwindow.h"

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
    void slotVarEditor();
    void slotProgEditor();
private slots:
    void editCommmande();
    void activerClavier(bool);
    void setMaxAffiche(int);


private:
    Ui::QComputer *ui;
};

#endif // QCOMPUTER_H
