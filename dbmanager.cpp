#include "dbmanager.h"
#include <QDebug>

DbManager* DbManager::instance = nullptr;

DbManager::DbManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("utcomputer.db");
    if (!db.open())
        qDebug() << "OPEN ERROR";
}

DbManager* DbManager::getInstance() {
    if (!instance)
        instance = new DbManager();
    return instance;
}

void DbManager::savePile() {
    //CREATE TABLE pile (id INTEGER PRIMARY KEY AUTOINCREMENT, typeLit VARCHAR NOT NULL, lit VARCHAR NOT NULL);

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
