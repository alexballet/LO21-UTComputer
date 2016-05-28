#include "computerexception.h"

ComputerException::ComputerException(const QString &str): info(str) {
    /*QMediaPlayer* player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("/home/anton/Projects/LO21/LO21-UTComputer/beep-07.wav"));
    player->setVolume(50);
    player->play();*/
}

ComputerException::ComputerException(const QString &str, const int n){
    /*QMediaPlayer* player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("/home/anton/Projects/LO21/LO21-UTComputer/beep-07.wav"));
    player->setVolume(50);
    player->play();*/
    QStringList l = str.split('$', QString::KeepEmptyParts);
    qDebug()<<l;
    info = l.at(0) + QString::number(n) + l.at(1);
}
