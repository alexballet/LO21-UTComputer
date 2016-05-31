#include "dbmanager.h"
#include <QDebug>

DbManager* DbManager::instance = nullptr;

DbManager::DbManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)[QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).length()-1]+"utcomputer.db";
    qDebug() << path;
    db.setDatabaseName(path);
    if (!db.open())
        qDebug() << "OPEN ERROR";
    QSqlQuery q(db);
    q.exec("CREATE TABLE pile (id INTEGER PRIMARY KEY AUTOINCREMENT, typeLit VARCHAR NOT NULL, lit VARCHAR NOT NULL)");
    qDebug()<<q.lastError();
    q.exec("CREATE TABLE variables (id INTEGER PRIMARY KEY AUTOINCREMENT, nameVar VARCHAR NOT NULL, typeLit VARCHAR NOT NULL, lit VARCHAR NOT NULL)");
    qDebug()<<q.lastError();
    q.exec("CREATE TABLE programs (id INTEGER PRIMARY KEY AUTOINCREMENT, nameProg VARCHAR NOT NULL, lit VARCHAR NOT NULL)");
    qDebug()<<q.lastError();

}

DbManager* DbManager::getInstance() {
    if (!instance)
        instance = new DbManager();
    return instance;
}

void DbManager::savePile() {

    QSqlQuery q(db);
    q.exec("DELETE FROM pile");
    qDebug()<<q.lastError();

    qDebug() << "SAVE PILE!";

    QStack<Litteral*>::iterator i;
    Pile* pile = Pile::getInstance();

    QSqlQuery query(db);
    query.clear();
    query.prepare("INSERT INTO pile (typeLit, lit)"
                  "VALUES (?, ?)");

    for (i = pile->getStack()->begin(); i != pile->getStack()->end(); ++i) {
        QString type = typeLitteral((*i)->toString());
        QString lit = (*i)->toString();
        query.addBindValue(type);
        query.addBindValue(lit);
        if (!query.exec())
        {
            qDebug() << query.lastError();
        }
        qDebug() << "Type: " << type << "lit: " << lit;
    }
}

void DbManager::saveVariables() {

    QSqlQuery q(db);
    q.exec("DELETE FROM variables");
    qDebug()<<q.lastError();

    qDebug() << "SAVE VARIABLES!";

    QMap<QString, Variable*>::const_iterator i;
    VariableMap* varMap = VariableMap::getInstance();

    QSqlQuery query(db);
    query.clear();
    query.prepare("INSERT INTO variables (nameVar, typeLit, lit)"
                  "VALUES (?, ?, ?)");

    for (i = varMap->getIteratorBegin(); i != varMap->getIteratorEnd(); ++i) {
        QString name = i.key();
        QString type = typeLitteral(i.value()->getValue()->toString());
        QString lit = i.value()->toString();
        query.addBindValue(type);
        query.addBindValue(lit);
        query.addBindValue(name);
        if (!query.exec())
        {
            qDebug() << query.lastError();
        }
        qDebug() << "Type: " << type << "lit: " << lit << "nomVar: " << name;
    }
}

void DbManager::savePrograms() {

    QSqlQuery q(db);
    q.exec("DELETE FROM programs");
    qDebug()<<q.lastError();

    qDebug() << "SAVE PROGRAMS!";

    QMap<QString, Programme*>::const_iterator i;
    ProgrammeMap* progMap = ProgrammeMap::getInstance();

    QSqlQuery query(db);
    query.clear();
    query.prepare("INSERT INTO programs (nameProg, lit)"
                  "VALUES (?, ?)");

    for (i = progMap->getIteratorBegin(); i != progMap->getIteratorEnd(); ++i) {
        QString name = i.key();
        QString lit = i.value()->toString();
        query.addBindValue(lit);
        query.addBindValue(name);
        if (!query.exec())
        {
            qDebug() << query.lastError();
        }
        qDebug() << "Lit: " << lit << "nomProg: " << name;
    }
}
