#include "computerexception.h"

ComputerException::ComputerException(const QString &str): info(str) {
    QSettings settings;
    if(settings.value("Bip")==true)
        playBeep();
}

ComputerException::ComputerException(const QString &str, const int n){
    QSettings settings;
    if(settings.value("Bip")==true)
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

QString ComputerException::getInfo() const {
    return info;
}
