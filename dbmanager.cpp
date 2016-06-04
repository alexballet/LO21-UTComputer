#include "dbmanager.h"
#include <QDebug>
#include <QCoreApplication>

DbManager* DbManager::instance = nullptr;

DbManager::DbManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString path = QCoreApplication::applicationDirPath()+"/utcomputer.db";
    db.setDatabaseName(path);
    if (!db.open())
        qDebug() << "OPEN ERROR";
    QSqlQuery query(db);
    if(!db.tables().contains("pile") && !db.tables().contains("variables") && !db.tables().contains("programs") && !db.tables().contains("options")){
        query.exec("CREATE TABLE pile (id INTEGER PRIMARY KEY AUTOINCREMENT, typeLit VARCHAR NOT NULL, lit VARCHAR NOT NULL)");
        qDebug()<<query.lastError();
        query.exec("CREATE TABLE variables (id INTEGER PRIMARY KEY AUTOINCREMENT, nameVar VARCHAR NOT NULL, typeLit VARCHAR NOT NULL, lit VARCHAR NOT NULL)");
        qDebug()<<query.lastError();
        query.exec("CREATE TABLE programs (id INTEGER PRIMARY KEY AUTOINCREMENT, nameProg VARCHAR NOT NULL, lit VARCHAR NOT NULL)");
        qDebug()<<query.lastError();
        query.exec("CREATE TABLE options (id INTEGER PRIMARY KEY AUTOINCREMENT, option VARCHAR NOT NULL, valeur INTEGER NOT NULL)");
        qDebug()<<query.lastError();
    }

}

DbManager* DbManager::getInstance() {
    if (!instance)
        instance = new DbManager();
    return instance;
}

void DbManager::savePile() {

    QSqlQuery query(db);
    query.exec("DELETE FROM pile");
    qDebug()<<query.lastError();

    QStack<Litteral*>::const_iterator i;
    Pile* pile = Pile::getInstance();

    query.clear();
    query.prepare("INSERT INTO pile (typeLit, lit)"
                  "VALUES (?, ?)");

    for (i = pile->getIteratorBegin(); i != pile->getIteratorEnd(); ++i) {
        QString type = typeLitteral((*i)->toString());
        QString lit = (*i)->toString();
        query.addBindValue(type);
        query.addBindValue(lit);
        if (!query.exec())
        {
            qDebug() << query.lastError();
        }
    }
}

void DbManager::saveVariables() {

    QSqlQuery query(db);
    query.exec("DELETE FROM variables");
    qDebug()<<query.lastError();


    QMap<QString, Variable*>::const_iterator i;
    VariableMap* varMap = VariableMap::getInstance();

    query.clear();
    query.prepare("INSERT INTO variables (nameVar, typeLit, lit)"
                  "VALUES (?, ?, ?)");

    for (i = varMap->getIteratorBegin(); i != varMap->getIteratorEnd(); ++i) {
        QString name = i.key();
        QString type = typeLitteral(i.value()->getValue()->toString());
        QString lit = i.value()->toString();
        query.addBindValue(name);
        query.addBindValue(type);
        query.addBindValue(lit);
        if (!query.exec())
        {
            qDebug() << query.lastError();
        }
    }
}

void DbManager::savePrograms() {

    QSqlQuery query(db);
    query.exec("DELETE FROM programs");
    qDebug()<<query.lastError();


    QMap<QString, Programme*>::const_iterator i;
    ProgrammeMap* progMap = ProgrammeMap::getInstance();

    query.clear();
    query.prepare("INSERT INTO programs (nameProg, lit)"
                  "VALUES (?, ?)");

    for (i = progMap->getIteratorBegin(); i != progMap->getIteratorEnd(); ++i) {
        QString name = i.key();
        QString lit = i.value()->toString();
        query.addBindValue(name);
        query.addBindValue(lit);
        if (!query.exec())
        {
            qDebug() << query.lastError();
        }
    }
}

void DbManager::saveOptions() {

    QSqlQuery query(db);
    query.exec("DELETE FROM options");
    qDebug()<<query.lastError();

    query.clear();
    query.prepare("INSERT INTO options (option, valeur)"
                  "VALUES (?, ?)");

    QSettings settings;
    foreach (const QString &str, settings.allKeys()) {
        query.addBindValue(str);
        query.addBindValue(settings.value(str).toInt());
        if (!query.exec()) {
            qDebug() << query.lastError();
        }
    }
}

void DbManager::setPile(){

    QSqlQuery query(db);
    query.clear();
    query.exec("SELECT * FROM pile");
    if (!query.exec())
    {
        qDebug() << query.lastError();
    }

    Pile* pile = Pile::getInstance();

    if( query.isSelect() ){
        while (query.next()) {
            QString type = query.value("typeLit").toString();
            QString lit = query.value("lit").toString();
            pile->push(Litteral::createLitteral(lit, type));
        }
    }
}

void DbManager::setVariables(){

    QSqlQuery query(db);
    query.clear();
    query.exec("SELECT * FROM variables");
    if (!query.exec())
    {
        qDebug() << query.lastError();
    }

    VariableMap* varMap = VariableMap::getInstance();

    if( query.isSelect() ){
        while (query.next()) {
            QString id = query.value("nameVar").toString();
            QString type = query.value("typeLit").toString();
            QString lit = query.value("lit").toString();
            Variable *var = new Variable(Litteral::createLitteral(lit, type), id);
            varMap->insertVar(id, var);
        }
    }
}

void DbManager::setPrograms(){

    QSqlQuery query(db);
    query.clear();
    query.exec("SELECT * FROM programs");
    if (!query.exec())
    {
        qDebug() << query.lastError();
    }

    ProgrammeMap* progMap = ProgrammeMap::getInstance();

    if( query.isSelect() ){
        while (query.next()) {
            QString id = query.value("nameProg").toString();
            QString lit = query.value("lit").toString();
            Programme *prog = new Programme(lit);
            prog->setId(id);
            progMap->insertProg(id, prog);
        }
    }
}

void DbManager::setOptions(){

    QSqlQuery query(db);
    query.clear();
    query.exec("SELECT * FROM options");
    if (!query.exec())
    {
        qDebug() << query.lastError();
    }
    QSettings settings;
    if( query.isSelect() ){
        while (query.next()) {
            QString option = query.value("option").toString();
            int valeur = query.value("valeur").toInt();
            settings.setValue(option, valeur);
        }
    }
}
