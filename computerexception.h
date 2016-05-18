#ifndef COMPUTEREXCEPTION_H
#define COMPUTEREXCEPTION_H

#include <QString>
#include <QMediaPlayer>

class ComputerException {
    QString info;
public:
    ComputerException(const QString& str);
    QString getInfo() const { return info; }
};

#endif // COMPUTEREXCEPTION_H
