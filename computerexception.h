#ifndef COMPUTEREXCEPTION_H
#define COMPUTEREXCEPTION_H

#include <QString>
#include <QSettings>
#include <QMediaPlayer>
/*!
 * \brief The ComputerException class manages to catch all the exceptions of the UTComputer.
 */
class ComputerException {
  private:
    /*!
     * \brief Explanation of the generated ComputerException.
     */
    QString info;
    /*!
     * \brief Method that plays a bip sound at each generated ComputerException (can be disabled in the settings).
     */
    void playBeep() const;
  public:
    /*!
     * \brief Constructor of ComputerException.
     * \param str - If n is not given as a parameter, the constructor initializes the info attribute with str. Otherwise, the ComputerException is generated because of an incorrect number of operands when applying a specific operator.
     * \param n - If it is not given, its default value is -1. Else, it represents the number of wanted operands when applying a specific operator.
     */
    ComputerException(const QString& str, const int n = -1);
    /*!
     * \brief Accessor of the info attribute.
     * \return It returns the info parameter.
     */
    QString getInfo() const;
};

#endif // COMPUTEREXCEPTION_H
