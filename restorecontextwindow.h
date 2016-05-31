#ifndef RESTORECONTEXTWINDOW_H
#define RESTORECONTEXTWINDOW_H

#include <QDialog>

namespace Ui {
class RestoreContextWindow;
}

class RestoreContextWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RestoreContextWindow(QWidget *parent = 0);
    ~RestoreContextWindow();

private:
    Ui::RestoreContextWindow *ui;
};

#endif // RESTORECONTEXTWINDOW_H
