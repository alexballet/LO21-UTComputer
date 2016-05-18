#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>

namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = 0);
    ~Options();

private slots:
    void activerClavierOpt(bool);
    void setMaxAfficheSlot(int);
signals:
    void activerClavierSig(bool);
    void setMaxAfficheSig(int);

private:
    Ui::Options *ui;
};

#endif // OPTIONS_H
