#include "expression.h"

Expression::Expression(QString t) : text(t) {

}

QString Expression::getText() const {
    return text;
}

QString Expression::toString() const {
    return "'" + text + "'";
}

bool isExpression(const QString& i){
    return i.at(0)=='\'' && i.at(i.length()-1)=='\'';
}
