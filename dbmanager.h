#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include "pile.h"

class DbManager {
private:
    static DbManager* instance;
    QSqlDatabase db;
    DbManager();
public:
    static DbManager* getInstance();
    void savePile();
    void saveVariables();
    void savePrograms();
    void setPile();
    void setVariables();
    void setPrograms();
};

#endif // DBMANAGER_H
