#-------------------------------------------------
#
# Project created by QtCreator 2016-05-07T11:42:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia sql

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
    options.cpp \
    variableeditor.cpp \
    programeditor.cpp \
    programeditorwindow.cpp \
    memento.cpp \
    dbmanager.cpp

HEADERS  += qcomputer.h \
    pile.h \
    litteral.h \
    computerexception.h \
    controleur.h \
    variable.h \
    atome.h \
    expression.h \
    programme.h \
    options.h \
    variableeditor.h \
    programeditor.h \
    operateur.h \
    programeditorwindow.h \
    memento.h \
    dbmanager.h

FORMS    += qcomputer.ui \
    options.ui \
    variableeditor.ui \
    programeditor.ui \
    programeditorwindow.ui
