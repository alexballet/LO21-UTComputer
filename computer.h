#ifndef _COMPUTER_H
#define _COMPUTER_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
using namespace std;

class ComputerException {
    QString info;
public:
    ComputerException(const QString& str):info(str){}
    QString getInfo() const { return info; }
};

class Expression {
    int value;
    Expression(int v):value(v){}
    Expression(const Expression& e);
    Expression& operator=(const Expression& e);
    friend class ExpressionManager;
public:
    QString toString() const;
    int getValue() const { return value; }
};



class ExpressionManager {
    Expression** exps;
    unsigned int nb;
    unsigned int nbMax;
    void agrandissementCapacite();
    ExpressionManager():exps(nullptr),nb(0),nbMax(0){}
    ~ExpressionManager();
    ExpressionManager(const ExpressionManager& m);
    ExpressionManager& operator=(const ExpressionManager& m);

    struct Handler{
        ExpressionManager* instance;
        Handler():instance(nullptr){}
        // destructeur appelé à la fin du programme
        ~Handler(){ delete instance; }
    };
    static Handler handler;
public:
    Expression& addExpression(int v);
    void removeExpression(Expression& e);
    static ExpressionManager& getInstance();
    static void libererInstance();
    class Iterator {
        friend class ExpressionManager;
        Expression** currentExp;
        unsigned int nbRemain;
        Iterator(Expression** u, unsigned nb):currentExp(u),nbRemain(nb){}
    public:
        Iterator():currentExp(nullptr),nbRemain(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw ComputerException("error, next on an iterator which is done");
            nbRemain--;
            currentExp++;
        }
        Expression& current() const {
            if (isDone())
                throw ComputerException("error, indirection on an iterator which is done");
            return **currentExp;
        }
    };
    Iterator getIterator() {
        return Iterator(exps,nb);
    }
    class iterator {
        Expression** current;
        iterator(Expression** u):current(u){}
        friend class ExpressionManager;
    public:
        iterator():current(0){}
        Expression& operator*() const { return **current; }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ ++current; return *this; }
    };
    iterator begin() { return iterator(exps); }
    iterator end() { return iterator(exps+nb); }

    class const_iterator {
        Expression** current;
        const_iterator(Expression** u):current(u){}
        friend class ExpressionManager;
    public:
        const_iterator():current(0){}
        Expression& operator*() const { return **current; }
        bool operator!=(const_iterator it) const { return current!=it.current; }
        const_iterator& operator++(){ ++current; return *this; }
    };
    const_iterator begin() const { return const_iterator(exps); }
    const_iterator end() const { return const_iterator(exps+nb); }
};


class Item {
    Expression* exp;
public:
    Item():exp(nullptr){}
    void setExpression(Expression& e) { exp=&e; }
    void raz() { exp=0; }
    Expression& getExpression() const;
};

class Pile : public QObject {
    Q_OBJECT

    Item* items;
    unsigned int nb;
    unsigned int nbMax;
    QString message;
    void agrandissementCapacite();
    unsigned int nbAffiche;
public:
    Pile():items(nullptr),nb(0),nbMax(0),message(""),nbAffiche(4){}
    ~Pile();
    void push(Expression& e);
    void pop();
    bool estVide() const { return nb==0; }
    unsigned int taille() const { return nb; }
    void affiche(QTextStream& f) const;
    Expression& top() const;
    void setNbItemsToAffiche(unsigned int n) { nb=n; }
    unsigned int getNbItemsToAffiche() const { return nbAffiche; }
    void setMessage(const QString& m) { message=m; modificationEtat(); }
    QString getMessage() const { return message; }
    class iterator {
        Item* current;
        iterator(Item* u):current(u){}
        friend class Pile;
    public:
        iterator():current(nullptr){}
        Expression& operator*() const { return current->getExpression(); }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ --current; return *this; }
    };
    iterator begin() { return iterator(items+nb-1); }
    iterator end() { return iterator(items-1); }

    class const_iterator {
        Item* current;
        const_iterator(Item* u):current(u){}
        friend class Pile;
    public:
        const_iterator():current(nullptr){}
        const Expression& operator*() const { return current->getExpression(); }
        bool operator!=(const_iterator it) const { return current!=it.current; }
        const_iterator& operator++(){ --current; return *this; }
    };
    const_iterator begin() const { return const_iterator(items+nb-1); }
    const_iterator end() const { return const_iterator(items-1); }

signals:
    void modificationEtat();
};

class Controleur {
    ExpressionManager& expMng;
    Pile& expAff;
public:
    Controleur(ExpressionManager& m, Pile& v):expMng(m), expAff(v){}
    void commande(const QString& c);

};

bool estUnOperateur(const QString s);
bool estUnNombre(const QString s);


#endif
