#-------------------------------------------------
#
# Project created by QtCreator 2016-05-07T11:42:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UTComputer
TEMPLATE = app


SOURCES += main.cpp\
        qcomputer.cpp \
    pile.cpp \
    litteral.cpp \
    computerexception.cpp \
    controleur.cpp \
    variable.cpp \
    atome.cpp \
    expression.cpp \
    programme.cpp \
    options.cpp

HEADERS  += qcomputer.h \
    pile.h \
    litteral.h \
    computerexception.h \
    controleur.h \
    variable.h \
    atome.h \
    expression.h \
    programme.h \
    options.h

FORMS    += qcomputer.ui \
    options.ui
