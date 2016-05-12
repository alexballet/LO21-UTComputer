#include "variable.h"

Variable::Variable(Litteral *v, QString id): value(v), id(id) {

}

const Litteral* Variable::getValue() const {
    return value;
}

QString Variable::getId() const {
    return id;
}

QString Variable::toString() const {
    return value->toString();
}
