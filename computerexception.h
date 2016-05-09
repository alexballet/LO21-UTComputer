#ifndef COMPUTEREXCEPTION_H
#define COMPUTEREXCEPTION_H


class ComputerException {
    QString info;
public:
    ComputerException(const QString& str):info(str){}
    QString getInfo() const { return info; }
};

#endif // COMPUTEREXCEPTION_H
