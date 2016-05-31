#ifndef COMPUTEREXCEPTION_H
#define COMPUTEREXCEPTION_H

#include <QString>
#include <QSettings>
#include <QMediaPlayer>

class ComputerException {
private:
    QString info;
    void playBeep() const;
public:
    ComputerException(const QString& str);
    ComputerException(const QString& str, const int n);
    QString getInfo() const { return info; }
};

#endif // COMPUTEREXCEPTION_H
