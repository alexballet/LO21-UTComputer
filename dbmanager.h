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
    //disabling copy and assignment
    DbManager& operator=(const DbManager&) = delete;
    DbManager (const DbManager&) = delete;
public:
    static DbManager* getInstance();
    void savePile();
    void saveVariables();
    void savePrograms();
    void saveOptions();
    void setPile();
    void setVariables();
    void setPrograms();
    void setOptions();
};

#endif // DBMANAGER_H
