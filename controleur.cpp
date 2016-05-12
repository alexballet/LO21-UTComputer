#include "controleur.h"
#include <QDebug>
#include <QRegularExpressionMatch>

Controleur* Controleur::instance = nullptr;

void Controleur::parse(const QString& com) {
    Pile* pile = Pile::getInstance();
    QStringList words = com.split(" ");

    foreach (QString word, words) {
        QString type = typeLitteral(word);
        if(type != "Inconnu")
            pile->push(word, type);
    }
}

QString typeLitteral(const QString& lit){
    if(lit.count('$')==1){
        qDebug()<<"complexe";
        return "Complexe";
    }
    else if(lit.count('.') == 1){
        qDebug()<<"reel";
        return "Reel";
    }
    else if(lit.count('/') == 1) {
        qDebug()<<"rationnel";
        return "Rationnel";
    }
    else if(lit.count('.') == 0 && (lit[0].isDigit() || (lit[0]=='-' && lit[1].isDigit()))){
        qDebug()<<"entier";
        return "Entier";
    }
    else {
        QRegularExpression re("[A-Z][A-Z0-9]*");
        QRegularExpressionMatch match = re.match(lit);
        qDebug() << match.captured(0);
        if (match.hasMatch() && match.captured(0) == lit) {
            qDebug()<<"atome";
            return "Atome";
        }
    }

    return "Inconnu";
}

Controleur* Controleur::getInstance() {
    if(!instance)
        instance = new Controleur();
    return instance;
}
