#include "qcomputer.h"
#include <QApplication>
#include <QCoreApplication>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("LO21StarTeam");
    QCoreApplication::setOrganizationDomain("lo21.com");
    QCoreApplication::setApplicationName("UTComputer");
    QComputer w;
    w.setWindowTitle("UTComputer");
    w.show();

    return a.exec();
}
