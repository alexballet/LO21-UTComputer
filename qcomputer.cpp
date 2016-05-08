#include "qcomputer.h"
#include "ui_qcomputer.h"

QComputer::QComputer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QComputer)
{
    // Create the object pointed by the class attributes
//        pile= new Pile;
//        controleur=new Controleur(ExpressionManager::getInstance(),*pile);
//        ui->vuePile->setRowCount(pile->getNbItemsToAffiche());
//        ui->vuePile->setColumnCount(1);
        //put the message read-only.
//        message->setReadOnly(true);

//        // inhibit modification
//        vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);

        //  create a list of tables "i:" for each line
        // and the items of each list.
//        QStringList numberList;
//        for(unsigned int i=pile->getNbItemsToAffiche(); i>0; i--) {
//            QString str= QString::number(i);
//            str+=" :";
//            numberList<<str;
//            // creation of the item of each line initialized with an empty chain (chaine vide).
//            ui->vuePile->setItem(i-1, 0, new QTableWidgetItem(""));
//    }
//        // print the label list on a vertial header.
//        ui->vuePile->setVerticalHeaderLabels(numberList);
//        // fixed width as a function of the number of items to print
//        ui->vuePile->setFixedHeight(pile->getNbItemsToAffiche()*ui->vuePile->rowHeight(0)+2);
//        // connection
//        connect(pile,SIGNAL(modificationEtat()),this,SLOT(refresh()));
//        // first message
//        pile->setMessage("Bienvenue !");
//        // Give the command bar some focus.
//        ui->commande->setFocus(Qt::OtherFocusReason);

            ui->setupUi(this);

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
//    // the message
//    ui->message->setText(pile->getMessage());
//    unsigned int nb=0;
//    // delete everything
//    for(unsigned int i=0; i<pile->getNbItemsToAffiche(); i++) ui->vuePile->item(i,0)->
//            setText("");
//    // update
//    for(Pile::iterator it=pile->begin(); it!=pile->end() && nb<pile->
//        getNbItemsToAffiche(); ++it, nb++){
//        ui->vuePile->item(pile->getNbItemsToAffiche()-1-nb,0)->setText((*it).toString());
//    }
}


void QComputer::on_commande_returnPressed()
{
//    // the actual message is not important anymore
//    pile->setMessage("");
//    // getting text for the command bar
//    QString c=ui->commande->text();
//    // extraction of each element from the line
//    //(we suppose that <space> is the field separator)
//    QTextStream stream(&c);
//    QString com;
//    do {
//        stream>>com; // element extraction
//        // send the command to the controller
//        if (com!="") controleur->commande(com);
//    }while (com!="");
//    // empty the command line
//    ui->commande->clear();
}

void QComputer::editCommmande(){
    QPushButton *button = (QPushButton*)sender();
    QString com = ui->commande->text();
    QString addedText="";
    if (button->text()!="<-" && button->text()!="CLEAR"){
        if (button->text()=="_")
            addedText = " ";
        else
            addedText = button->text();
    }

    if(button->text()=="<-"){
        com.truncate(com.length()-1);
        ui->commande->setText(com);
    }
    ui->commande->setText(com+addedText);
}



void QComputer::on_activerClavier_stateChanged(int state)
{
    if(state){
        ui->clavier->show();
        ui->opLogiques->show();
        ui->opNumeriques->show();
        ui->opPile->show();
        this->setFixedSize(589,750);
    }
    else{
        ui->clavier->hide();
        ui->opLogiques->hide();
        ui->opNumeriques->hide();
        ui->opPile->hide();
        this->setFixedSize(589,322);
    }
}
