#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>

namespace Ui {
class Options;
}

/*!
 * \brief Window where the user can change app settings
 */
class Options : public QDialog {
    Q_OBJECT

  public:
    /*!
     * \brief Options constructor, sets up the ui, connects all signals.
     */
    explicit Options(QWidget *parent = 0);
    /*!
     * \brief Options destructor, deletes the ui.
     */
    ~Options();

  private slots:
    /*!
     * \brief Slot called when the user modifies the activerClavier checkbox.
     * The QSettings object is updated and activerClavierSig signal is sent to QComputer.
     * QComputer catches the signal and updates its state.
     */
    void activerClavierOpt(bool);
    /*!
     * \brief Slot called when the user modifies the dial. The dial controls the number of values displayed in the Pile tableWidget.
     * The QSettings object is updated and setMaxAfficheSig signal is sent to QComputer.
     * QComputer catches the signal and updates its state.
     */
    void setMaxAfficheSlot(int);
    /*!
     * \brief Slot called when the user modifies the activerBip checkbox.
     * The QSettings object is updated.
     * This affects the ComputerException constructor which will play a beep sound if the settings 'beep' value is set to true.
     */
    void activerBipOpt(bool);

  signals:
    void activerClavierSig(bool);
    void setMaxAfficheSig(int);

  private:
    /*!
     * \brief ui for Qt Designer
     */
    Ui::Options *ui;
};

#endif // OPTIONS_H
