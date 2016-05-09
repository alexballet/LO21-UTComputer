#ifndef _COMPUTER_H
#define _COMPUTER_H

#include <QObject>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QStack>

class ComputerException {
    QString info;
public:
    ComputerException(const QString& str):info(str){}
    QString getInfo() const { return info; }
};


class Litteral {



};

class Pile : public QObject {
    Q_OBJECT

    QStack<Litteral*> stack;
    QString message;
    Pile(): message(""){}
    static Pile* instance;

public:
    static Pile* getInstance();
    static void libererInstance();
    QString getMessage() const;
    void setMessage(const QString& msg);
};




/*
class Pile : public QObject {
    Q_OBJECT

//    Item* items;
//    unsigned int nb;
//    unsigned int nbMax;
//    QString message;
//    unsigned int nbAffiche;
public:
//    ~Pile();
//    void affiche(QTextStream& f) const;
//    Expression& top() const;
//    void setNbItemsToAffiche(unsigned int n) { nb=n; }
//    unsigned int getNbItemsToAffiche() const { return nbAffiche; }
//    void setMessage(const QString& m) { message=m; modificationEtat(); }
//    QString getMessage() const { return message; }
//    class iterator {
    //        Item* current;
    //        iterator(Item* u):current(u){}
    //        friend class Pile;
    //    public:
    //        iterator():current(nullptr){}
    //        Expression& operator*() const { return current->getExpression(); }
    //        bool operator!=(iterator it) const { return current!=it.current; }
    //        iterator& operator++(){ --current; return *this; }
    //    };
    //    iterator begin() { return iterator(items+nb-1); }
    //    iterator end() { return iterator(items-1); }

    //class const_iterator {
    //        Item* current;
    //        const_iterator(Item* u):current(u){}
    //        friend class Pile;
    //    public:
    //        const_iterator():current(nullptr){}
    //        const Expression& operator*() const { return current->getExpression(); }
    //        bool operator!=(const_iterator it) const { return current!=it.current; }
    //        const_iterator& operator++(){ --current; return *this; }
    //    };
    //    const_iterator begin() const { return const_iterator(items+nb-1); }
    //    const_iterator end() const { return const_iterator(items-1); }

//signals:
//    void modificationEtat();
};

class Controleur {
//    ExpressionManager& expMng;
//    Pile& expAff;
//public:
//    Controleur(ExpressionManager& m, Pile& v):expMng(m), expAff(v){}
    void commande(const QString& c);
};

bool estUnOperateur(const QString s);
bool estUnNombre(const QString s);
*/

#endif
