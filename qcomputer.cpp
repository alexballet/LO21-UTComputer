#include "qcomputer.h"
#include "ui_qcomputer.h"
#include "dbmanager.h"


QComputer::QComputer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QComputer) {

    ui->setupUi(this);

    restoreContext();

    Pile* pile = Pile::getInstance();

    initMenuBar();

    initPile();

    // Give the command bar some focus.
    ui->commande->setFocus(Qt::OtherFocusReason);

    //connect all the keyboard buttons
    QList<QPushButton*> buttons = this->findChildren<QPushButton*>();
    foreach (QPushButton * button, buttons) {
        connect(button, SIGNAL(released()), this, SLOT(editCommmande()));
    }

    //set initial memento
    Controleur::addMementoState(pile->createMemento());

    //Undo and Redo
    QShortcut* undo = new QShortcut(QKeySequence::Undo, this);
    connect(undo, SIGNAL(activated()), ui->UNDO, SLOT(click()));

    QShortcut* redo = new QShortcut(QKeySequence::Redo, this);
    connect(redo, SIGNAL(activated()), ui->REDO, SLOT(click()));

    refresh();
}

QComputer::~QComputer() {
    //save context before exiting
    DbManager *dbman = DbManager::getInstance();
    dbman->savePile();
    dbman->saveVariables();
    dbman->savePrograms();
    dbman->saveOptions();
    delete ui;
}

void QComputer::refresh() {
    Pile* pile = Pile::getInstance();

    // the message
    ui->message->setText(pile->getMessage());

    // delete everything
    for(unsigned int i = 0; i < pile->getMaxAffiche(); i++)
        ui->vuePile->item(i, 0)->setText("");

    // update
    unsigned int nb = 0;
    QStack<Litteral*>::const_iterator it;

    for(it = pile->getIteratorEnd() - 1 ; it != pile->getIteratorBegin() - 1 && nb < pile->getMaxAffiche(); nb++, --it) {
        ui->vuePile->item(pile->getMaxAffiche() - nb - 1, 0)->setText((*it)->toString());
    }
}


void QComputer::on_commande_returnPressed() {
    Pile* pile = Pile::getInstance();
    Controleur* controleur = Controleur::getInstance();

    // the actual message is not important anymore
    pile->setMessage("");

    // getting text for the command bar
    QString c = ui->commande->text();

    try {
        controleur->parse(c);
    } catch(ComputerException c) {
        pile->setMessage(c.getInfo());
    }

    // empty the command line
    ui->commande->clear();
    emit pile->modificationEtat();
}

void QComputer::editCommmande() {
    QPushButton *button = (QPushButton*)sender();
    QString com = ui->commande->text();
    QString addedText = "";

    if((isOperatorNum(button->text()) && button->text() != "/" && button->text() != "$" && button->text() != "-") || isOperatorLog(button->text()) || isOperatorPile(button->text())) {
        ui->commande->setText(com + button->text());
        emit ui->commande->returnPressed();
    } else {
        if (button->objectName() != "DELETE" && button->objectName() != "EMPTY" && button->objectName() != "SEND" && button->objectName() != "UNDO" && button->objectName() != "REDO") {
            if (button->text() == "_")
                addedText = " ";
            else
                addedText = button->text();
        } else if(button->text() == "<-") {
            com.truncate(com.length() - 1);
            ui->commande->setText(com);
        } else if(button->text() == "SEND") {
            emit ui->commande->returnPressed();
            return;
        } else if(button->text() == "EMPTY") {
            ui->commande->clear();
            return;
        } else if(button->text() == "UNDO") {
            try {
                Controleur::undo();
            } catch (ComputerException c) {
                Pile* pile = Pile::getInstance();
                pile->setMessage(c.getInfo());
                refresh();
            }

            return;
        } else if(button->text() == "REDO") {
            try {
                Controleur::redo();
            } catch (ComputerException c) {
                Pile* pile = Pile::getInstance();
                pile->setMessage(c.getInfo());
                refresh();
            }

            return;
        }

        ui->commande->setText(com + addedText);
    }
}



void QComputer::activerClavier(bool state) {
    if(state) {
        ui->clavier->show();
        ui->opLogiques->show();
        ui->opNumeriques->show();
        ui->opPile->show();
        this->setFixedSize(589, 776);
    } else {
        ui->clavier->hide();
        ui->opLogiques->hide();
        ui->opNumeriques->hide();
        ui->opPile->hide();
        this->setFixedSize(589, 322);
    }
}

void QComputer::setMaxAffiche(int n) {
    Pile* pile = Pile::getInstance();
    pile->setMaxAffiche(n);
    ui->vuePile->setRowCount(n);
    QStringList numberList;

    for(unsigned int i = n; i > 0; i--) {
        QString str = QString::number(i);
        str += " :";
        numberList << str;
        // creation of the item of each line initialized with an empty string (chaine vide).
        ui->vuePile->setItem(i - 1, 0, new QTableWidgetItem(""));
    }

    ui->vuePile->setVerticalHeaderLabels(numberList);
    ui->vuePile->setFixedHeight(n * ui->vuePile->rowHeight(0) + 2);
    emit pile->modificationEtat();

}


void QComputer::slotOptions() {
    Options opt;
    opt.setModal(true);
    connect(&opt, SIGNAL(activerClavierSig(bool)), this, SLOT(activerClavier(bool)));
    connect(&opt, SIGNAL(setMaxAfficheSig(int)), this, SLOT(setMaxAffiche(int)));
    opt.exec();
}

void QComputer::slotVarEditor() {
    VariableEditor varEditor;
    varEditor.setModal(true);
    varEditor.exec();
}

void QComputer::slotProgEditor() {
    ProgramEditor progEditor;
    progEditor.setModal(true);
    progEditor.exec();
}

void QComputer::restoreContext() {

    QMessageBox messageBox(QMessageBox::Question, tr("Restaurer contexte"),
                           tr("Voulez-vous restaurer la dernière session ?"),
                           QMessageBox::Yes | QMessageBox::No);

    messageBox.setButtonText(QMessageBox::Yes, tr("Oui"));
    messageBox.setButtonText(QMessageBox::No, tr("Non"));

    int ret = messageBox.exec();

    Pile* pile = Pile::getInstance();
    QSettings settings;

    switch (ret) {
    case QMessageBox::Yes: {
        DbManager *dbman = DbManager::getInstance();
        dbman->setOptions();
        dbman->setPile();
        dbman->setVariables();
        dbman->setPrograms();
        pile->setMaxAffiche(settings.value("Pile").toUInt());

        int state = settings.value("Clavier").toInt();

        if(state) {
            ui->clavier->show();
            ui->opLogiques->show();
            ui->opNumeriques->show();
            ui->opPile->show();
            this->setFixedSize(589, 776);
        } else {
            ui->clavier->hide();
            ui->opLogiques->hide();
            ui->opNumeriques->hide();
            ui->opPile->hide();
            this->setFixedSize(589, 322);
        }

        break;
    }

    case QMessageBox::No: {
        pile->setMaxAffiche(4);
        settings.setValue("Pile", 4);

        //keyboard enabled at start
        settings.setValue("Clavier", true);
        this->setFixedSize(589, 776);

        //disable bip sound
        settings.setValue("Bip", true);
        break;
    }

    default:
        break;
    }
}

void QComputer::initMenuBar() {
    //menu bar
    QMenuBar* menuBar = new QMenuBar();

    //File menu
    QMenu *fileMenu = new QMenu("Fichiers");
    menuBar->addMenu(fileMenu);
    QAction* actionOptions = fileMenu->addAction("Options");
    QAction* actionExit = fileMenu->addAction("Exit");

    //Editors
    QMenu *editorsMenu = new QMenu("Editors");
    menuBar->addMenu(editorsMenu);
    QAction* actionVarEditor = editorsMenu->addAction("Variable editor");
    QAction* actionProgEditor = editorsMenu->addAction("Program editor");

    this->layout()->setMenuBar(menuBar);

    //ouvrir la fenetre "options"
    connect(actionOptions, SIGNAL(triggered()), this, SLOT(slotOptions()));
    //ouvrir l'editeur de variables
    connect(actionVarEditor, SIGNAL(triggered()), this, SLOT(slotVarEditor()));
    //ouvrir l'editeur de programmes
    connect(actionProgEditor, SIGNAL(triggered()), this, SLOT(slotProgEditor()));
    //quitter
    connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));
}

void QComputer::initPile() {
    Pile* pile = Pile::getInstance();
    ui->vuePile->setRowCount(pile->getMaxAffiche());
    ui->vuePile->setColumnCount(1);
    ui->vuePile->verticalHeader()->setSectionResizeMode (QHeaderView::Fixed);

    QStringList numberList;

    for(unsigned int i = pile->getMaxAffiche(); i > 0; i--) {
        QString str = QString::number(i);
        str += " :";
        numberList << str;
        // creation of the item of each line initialized with an empty string (chaine vide).
        ui->vuePile->setItem(i - 1, 0, new QTableWidgetItem(""));
    }

    ui->vuePile->setVerticalHeaderLabels(numberList);
    ui->vuePile->setFixedHeight(pile->getMaxAffiche() * ui->vuePile->rowHeight(0) + 2);

    // inhibit modification
    ui->vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // connection
    connect(pile, SIGNAL(modificationEtat()), this, SLOT(refresh()));

    // first message
    pile->setMessage("Bienvenue !");

}
