#include "computerexception.h"

ComputerException::ComputerException(const QString &str): info(str) {
    playBeep();
}

ComputerException::ComputerException(const QString &str, const int n){
    playBeep();
    QStringList l = str.split('$', QString::KeepEmptyParts);
    qDebug()<<l;
    info = l.at(0) + QString::number(n) + l.at(1);
}

void ComputerException::playBeep() const {
    QMediaPlayer* player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/beep-07.wav"));
    player->setVolume(50);
    player->play();
}
