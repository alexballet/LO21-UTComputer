#include "controleur.h"
#include <QDebug>

Controleur* Controleur::instance = nullptr;

void Controleur::parse(const QString& com) {
    Pile* pile = Pile::getInstance();
    QStringList words = com.split(" ");

    foreach (QString word, words) {
        if(word.count('.') == 1){
            pile->push(word, "Reel");
        }
        else if(word.count('/') == 1) {
            pile->push(word, "Rationnel");
        }
        else if(word.count('.') == 0 && word[0].isDigit()) {
            pile->push(word, "Entier");
        }

        else
            pile->setMessage("Litteral " + word + " inconnu");
    }
}

Controleur* Controleur::getInstance() {
    if(!instance)
        instance = new Controleur();
    return instance;
}
