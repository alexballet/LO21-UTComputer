#include "qcomputer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QComputer w;
    w.setWindowTitle("UTComputer");
    w.show();

    return a.exec();
}
