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
    static int getAnswer();
private slots:
    void on_restore_accepted();

    void on_restore_rejected();

    void on_RestoreContextWindow_finished();

private:
    Ui::RestoreContextWindow *ui;
    static int answer;
};

#endif // RESTORECONTEXTWINDOW_H
