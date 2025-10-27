/*
 * Simple dialog for when the game is over with options to close game or
 * start a new one.
 *
 * Written by:
 *  Name: Jonatan Tevaniemi
 *  Student number: 150176680
 *  Username: cnjote
 *  E-mail: jonatantevaniemi@tuni.fi
 */
#ifndef GAMEOVERDIALOG_HH
#define GAMEOVERDIALOG_HH

#include <QDialog>

namespace Ui {
class GameOverDialog;
}

class GameOverDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameOverDialog(QWidget *parent = nullptr);
    ~GameOverDialog();

signals:
    // Emitted if user wants a new game
    void resetGameRequested();

public slots:
    // For setting the final time to display
    void setTime(const QString& time);

private slots:
    void on_closeButton_clicked();

    void on_newGameButton_clicked();

private:
    Ui::GameOverDialog *ui;
};

#endif // GAMEOVERDIALOG_HH
