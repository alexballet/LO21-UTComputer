#include "computerexception.h"

ComputerException::ComputerException(const QString &str, const int n) {
    if(n == -1) {
        info = str;
    } else {
        QStringList l = str.split('$', QString::KeepEmptyParts);
        info = l.at(0) + QString::number(n) + l.at(1);
    }

    QSettings settings;

    if(settings.value("Bip") == true)
        playBeep();
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
