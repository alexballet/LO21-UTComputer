#include "qcomputer.h"
#include "ui_qcomputer.h"

QComputer::QComputer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QComputer)
{
    // Create the object pointed by the class attributes
        pile= new Pile;
        controleur=new Controleur(ExpressionManager::getInstance(),*pile);
        message=new QLineEdit(this);
        vuePile=new QTableWidget(pile->getNbItemsToAffiche(),1,this); // 1 colonne !!!
        commande=new QLineEdit(this);
        couche = new QVBoxLayout(this);
        // Position the objects on the application window.
        couche->addWidget(message);
        couche->addWidget(vuePile);
        couche->addWidget(commande);
        setLayout(couche);
        // Put a title on the application windows
        this->setWindowTitle(QString("UTComputer"));
        // Color the message bar ant put it read-only.
        message->setStyleSheet("background: darkblue; color: yellow");
        message->setReadOnly(true);
        // Finish up the appearance of the object pointed by vuePile.
        // background
        vuePile->setStyleSheet("background: darkcyan; color: white");
        // foreground
        vuePile->verticalHeader()->setStyleSheet("color: black");
        // inhibit modification
        vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);
        // make invisible the column table.
        vuePile->horizontalHeader()->setVisible(false);
        // adjust automatically the window's width.
        vuePile->horizontalHeader()->setStretchLastSection(true);

        //  create a list of tables "i:" for each line
        // and the items of each list.
        QStringList numberList;
        for(unsigned int i=pile->getNbItemsToAffiche(); i>0; i--) {
            QString str= QString::number(i);
            str+=" :";
            numberList<<str;
            // creation of the item of each line initialized with an empty chain (chaine vide).
            vuePile->setItem(i-1, 0, new QTableWidgetItem(""));
    }
        // print the label list on a vertial header.
        vuePile->setVerticalHeaderLabels(numberList);
        // fixed width as a function of the number of items to print
        vuePile->setFixedHeight(pile->getNbItemsToAffiche()*vuePile->rowHeight(0)+2);
        // connection
        connect(pile,SIGNAL(modificationEtat()),this,SLOT(refresh()));
        connect(commande,SIGNAL(returnPressed()),this,SLOT(getNextCommande()));
        // first message
        pile->setMessage("Bienvenue !");
        // Give the command bar some focus.
        commande->setFocus(Qt::OtherFocusReason);
    ui->setupUi(this);
}

QComputer::~QComputer()
{
    delete ui;
}
void QComputer::refresh(){
    // the message
    message->setText(pile->getMessage());
    unsigned int nb=0;
    // delete everything
    for(unsigned int i=0; i<pile->getNbItemsToAffiche(); i++) vuePile->item(i,0)->
            setText("");
    // update
    for(Pile::iterator it=pile->begin(); it!=pile->end() && nb<pile->
        getNbItemsToAffiche(); ++it, nb++){
        vuePile->item(pile->getNbItemsToAffiche()-1-nb,0)->setText((*it).toString()
                                                                   );
    }
}
void QComputer::getNextCommande(){
    // the actual message is not important anymore
    pile->setMessage("");
    // getting text for the command bar
    QString c=commande->text();
    // extraction of each element from the line
    //(we suppose that <space> is the field separator)
    QTextStream stream(&c);
    QString com;
    do {
        stream>>com; // element extraction
        // send the command to the controller
        if (com!="") controleur->commande(com);
    }while (com!="");
    // empty the command line
    commande->clear();
}
