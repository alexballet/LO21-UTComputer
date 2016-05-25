#pragma once
//#include "pile.h"
#include "litteral.h"
#include <QStack>

class Memento {
private:
    friend class Pile;
    QStack<Litteral*> state;
public:
    Memento(QStack<Litteral*> s);
};

