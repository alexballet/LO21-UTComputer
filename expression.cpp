#include "expression.h"

Expression::Expression(QString t) : text(t) {

}

QString Expression::getText() const {
    return text;
}

QString Expression::toString() const {
    return "'" + text + "'";
}
