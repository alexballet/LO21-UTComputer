#ifndef OPERATEUR_H
#define OPERATEUR_H

#include <QString>
#include <QMap>
#include <QList>

static const QMap<QString, int> opsNum{
    {"+", 2},
    {"-", 2},
    {"*", 2},
    {"/", 2},
    {"DIV", 2},
    {"MOD", 2},
    {"NEG", 1},
    {"NUM", 1},
    {"DEN", 1},
    {"$", 2},
    {"RE", 1},
    {"IM", 1},
    {"SIN", 1},
    {"ARCSIN", 1},
    {"COS", 1},
    {"ARCCOS", 1},
    {"TAN", 1},
    {"ARCTAN", 1},
    {"EXP", 1},
    {"LN", 1}
    };

static const QMap<QString, int> opsLog{
    {"=", 2},
    {"!=", 2},
    {"<", 2},
    {">", 2},
    {">=", 2},
    {"<=", 2},
    {"AND", 2},
    {"OR", 2},
    {"NOT", 1}
    };

static const QMap<QString, int> opsPile{
    {"DUP", 0},
    {"SWAP", 2},
    {"LASTOP", 0},
    {"CLEAR", 0},
    {"EVAL", 1},
    {"STO", 2},
    {"FORGET", 1},
    {"EDIT", 1},
    {"IFT", 2},
    {"DROP", 0}
    };

#endif // OPERATEUR_H
