/*
 * Simple dialog if the starting parameters for a new game were invalid.
 *
 * Written by:
 *  Name: Jonatan Tevaniemi
 *  Student number: 150176680
 *  Username: cnjote
 *  E-mail: jonatantevaniemi@tuni.fi
 */
#ifndef INVALIDSTARTDIALOG_HH
#define INVALIDSTARTDIALOG_HH

#include <QDialog>

namespace Ui {
class InvalidStartDialog;
}

class InvalidStartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InvalidStartDialog(const QString& errorMessage,
                                QWidget *parent = nullptr);
    ~InvalidStartDialog();

private:
    Ui::InvalidStartDialog *ui;
};

#endif // INVALIDSTARTDIALOG_HH
