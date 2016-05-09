#include "qcomputer.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QComputer w;
    qDebug() << "lel";
    w.setWindowTitle("UTComputer");
    w.show();

    return a.exec();
}
