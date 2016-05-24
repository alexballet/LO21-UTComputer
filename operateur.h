#ifndef OPERATEUR_H
#define OPERATEUR_H

#include <QString>
#include <QMap>
#include <QList>

static const QMap<QString, int> ops{
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

#endif // OPERATEUR_H
