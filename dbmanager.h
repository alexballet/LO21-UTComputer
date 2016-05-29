#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "pile.h"

class DbManager {
private:
    static DbManager* instance;
    QSqlDatabase db;
    DbManager();
public:
    static DbManager* getInstance();
    void savePile();
};

#endif // DBMANAGER_H
