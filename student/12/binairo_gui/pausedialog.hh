/*
 * Simple dialog for when the game is paused. Stops timer and disables user
 * from making any modifications to the board.´
 *
 * Written by:
 *  Name: Jonatan Tevaniemi
 *  Student number: 150176680
 *  Username: cnjote
 *  E-mail: jonatantevaniemi@tuni.fi
 */
#ifndef PAUSEDIALOG_HH
#define PAUSEDIALOG_HH

#include <QDialog>

namespace Ui {
class PauseDialog;
}

class PauseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PauseDialog(QWidget *parent = nullptr);
    ~PauseDialog();

signals:
    // This is caught by mainwindow and it just starts the timer back up.
    void resumeGame();

protected:
    // Have to override this because timer has to be started even if it's
    // closed from the close sign
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_resumeButton_pressed();

private:
    Ui::PauseDialog *ui;
};

#endif // PAUSEDIALOG_HH
