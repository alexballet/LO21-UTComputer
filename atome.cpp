#include "atome.h"

Atome::Atome(QString id): id(id) {

}

QString Atome::getId() const {
    return id;
}

QString Atome::toString() const {
    return id;
}

Litteral* Atome::getLitterale() const {
    return new Variable(new Entier(5), id);
}
