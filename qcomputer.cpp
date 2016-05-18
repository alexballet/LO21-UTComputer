#include "qcomputer.h"
#include "ui_qcomputer.h"
#include <QStringList>
#include <QTableView>
#include <QTableWidgetItem>
#include <QMenuBar>

QComputer::QComputer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QComputer)
{
    Pile* pile = Pile::getInstance();

    ui->setupUi(this);

    //menu bar
    QMenuBar* menuBar = new QMenuBar();
    //File menu
    QMenu *fileMenu = new QMenu("File");
    menuBar->addMenu(fileMenu);
    QAction* action = fileMenu->addAction("Options");
    fileMenu->addAction("Exit");

    //Editors
    QMenu *editorsMenu = new QMenu("Editors");
    menuBar->addMenu(editorsMenu);
    editorsMenu->addAction("Variable editor");
    editorsMenu->addAction("Program editor");

    this->layout()->setMenuBar(menuBar);

    connect(action, SIGNAL(triggered()),this,SLOT(slotOptions()));
    //Ui::Options *ui2 = new Ui::Options;
    //connect(ui2->activerClavier, SIGNAL(toggled(int)), this, SLOT(activerClavier(int));

    ui->vuePile->setRowCount(pile->getMaxAffiche());
    ui->vuePile->setColumnCount(1);
    ui->vuePile->verticalHeader()->setSectionResizeMode (QHeaderView::Fixed);

    QStringList numberList;
    for(unsigned int i = pile->getMaxAffiche(); i>0; i--) {
        QString str = QString::number(i);
        str += " :";
        numberList << str;
        // creation of the item of each line initialized with an empty string (chaine vide).
        ui->vuePile->setItem(i-1, 0, new QTableWidgetItem(""));
    }
    ui->vuePile->setVerticalHeaderLabels(numberList);
    ui->vuePile->setFixedHeight(pile->getMaxAffiche() * ui->vuePile->rowHeight(0)+2);

    // inhibit modification
    ui->vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // connection
    connect(pile,SIGNAL(modificationEtat()),this,SLOT(refresh()));

    // first message
    pile->setMessage("Bienvenue !");

    // set ui message
    ui->message->setText(pile->getMessage());

    // Give the command bar some focus.
    ui->commande->setFocus(Qt::OtherFocusReason);

    //connect all the keyboard buttons
    QList<QPushButton*> buttons = this->findChildren<QPushButton*>();
    foreach (QPushButton *button, buttons){
        connect(button, SIGNAL(released()), this, SLOT(editCommmande()));
    }



    //disable keyboard
    this->setFixedSize(589,322);
    ui->clavier->hide();
    ui->opLogiques->hide();
    ui->opNumeriques->hide();
    ui->opPile->hide();
}

QComputer::~QComputer()
{
    delete ui;
}

void QComputer::refresh(){
    Pile* pile = Pile::getInstance();
    // the message
    ui->message->setText(pile->getMessage());

    unsigned int nb = 0;
    // delete everything
    for(unsigned int i=0; i<pile->getMaxAffiche(); i++)
        ui->vuePile->item(i,0)->setText("");
    // update
    QVectorIterator<Litteral*> it(*pile->getStack());
    for(it.toBack() ; it.hasPrevious() && nb<pile->getMaxAffiche(); nb++){
        ui->vuePile->item(pile->getMaxAffiche()-1-nb,0)->setText(it.previous()->toString());
    }
}


void QComputer::on_commande_returnPressed()
{
    Pile* pile = Pile::getInstance();
    Controleur* controleur = Controleur::getInstance();
    // the actual message is not important anymore
    pile->setMessage("");
    // getting text for the command bar
    QString c = ui->commande->text();
    // extraction of each element from the line
    //(we suppose that <space> is the field separator)
    QTextStream stream(&c);
    QString com;
    do {
        stream >> com; // element extraction
        // send the command to the controller
        if (com != "")
            controleur->parse(com);
    }while (com != "");
    // empty the command line
    ui->commande->clear();
    emit pile->modificationEtat();
}

void QComputer::editCommmande(){
    QPushButton *button = (QPushButton*)sender();
    QString com = ui->commande->text();
    QString addedText="";
    if (button->objectName() !="DELETE" && button->objectName()!="EMPTY" && button->objectName() != "SEND"){
        if (button->text()=="_")
            addedText = " ";
        else
            addedText = button->text();
    }

    if(button->text()=="<-"){
        com.truncate(com.length()-1);
        ui->commande->setText(com);
    }
    if(button->text()=="SEND"){
        emit ui->commande->returnPressed();
        return;
    }
    ui->commande->setText(com+addedText);
}



void QComputer::activerClavier(bool state)
{
    if(state){
        ui->clavier->show();
        ui->opLogiques->show();
        ui->opNumeriques->show();
        ui->opPile->show();
        this->setFixedSize(589,776);
    }
    else{
        ui->clavier->hide();
        ui->opLogiques->hide();
        ui->opNumeriques->hide();
        ui->opPile->hide();
        this->setFixedSize(589,322);
    }
}

void QComputer::slotOptions() {
    Options opt;
    opt.setModal(true);
    connect(&opt, SIGNAL(activerClavierSig(bool)), this, SLOT(activerClavier(bool)));
    //connect(&opt, SIGNAL(toggled(int)), this, SLOT(activerClavier(int)));
    opt.exec();
}
