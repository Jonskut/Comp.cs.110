/*
 * Binairo GUI
 * Please go to main.cpp for more comprehensive comments
 * or see instructions.txt.
 *
 * This file defines the central widget and window that contains
 * all of the widgets in the GUI.
 *
 * The start screen is mainly made in Designer. It has all the necessary
 * buttons and fields to start a new game.
 *
 * Once a new game is started, the central widget is deleted and a new one
 * with the gameboard, timer and relevant buttons.
 *
 * Everything in the GUI except the gameboard widget (and dialogs)
 * are defined here.
 *
 * Written by:
 *  Name: Jonatan Tevaniemi
 *  Student number: 150176680
 *  Username: cnjote
 *  E-mail: jonatantevaniemi@tuni.fi
 */
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QLabel>
#include <QPainter>
#include <QProcess>
#include <QTimer>
#include <QScrollArea>

#include <gameboard.hh>
#include <gameboardwidget.hh>
#include "invalidstartdialog.hh"
#include "gameoverdialog.hh"
#include "pausedialog.hh"
#include "utils.hh"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Error and information outputs
    const QString NOT_CHECKED = "No selected input option. \n"
                                "Please select random or manual input.";

    const QString WRONG_LENGTH = "Wrong input text length. Please refer to \n"
                                 "the instruction manual for help.";

    const QString WRONG_CHARACTERS = "Wrong characters in input text. \n"
                                     "Please use only 0, 1, and ' '"
                                     " (whitespace)";

    const QString BAD_SEED_LIST = "Bad seed (impossible to solve). \n"
                                  "Please try another.";

    const QString BAD_SEED_CHAR = "Bad seed (input is not an integer): \n"
                                  "Please input only integers.";

    const QString BAD_INPUT = "Bad input (illegal board). \n"
                              "Please try another input.";

    const QString MANUAL_HELPTEXT = "Input a string of size "
                                    + QString::number(SIZE*SIZE) +
                                    ".\nAllowed characters are "
                                    "'0', '1' and ' ' (whitespace).";

     const QString SEED_HELPTEXT = "Input a seed.\n"
                                   "Seed should be an integer. ";

    // Other constants
    const int GRID_SIDE = 50;

signals:
    // Emitted when "Start Over" is pressed, caught by GameBoardWidget
    // to clear board (except dotted cells).
    void requestClearBoard();

private slots:
    // Tries to fill board, and if successful, calls drawBoard().
    void on_startButton_clicked();
    // Sets the helptext to manual helptext
    void on_manualButton_clicked();
    // Sets the helptext to random helptext
    void on_randomButton_clicked();

private:
    Ui::MainWindow *ui;

    // Gameboard related stuff
    GameBoard board;
    GameBoardWidget *boardWidget = nullptr;

    // Layout during game
    QLayout *gameLayout;

    // This method handles the initialization of the new central widget.
    // It deletes the old one, creates a new one and creates new widgets to put
    // in gameLayout. It also defines a minimum window size and sizes the
    // window to look neat.
    void drawBoard();

    // This method pauses the timer and shows the dialog at the end of game
    void showGameOverDialog();
    // This method pauses the timer and shows the paused dialog
    void showPauseDialog();


  // This method tries to fill the gameboard.
  // Many of these checks exist in gameboard.cpp, but we need (read: I want)
  // custom error messages which can't be done properly using gameboard.

  // Returns false and sets error message Qstring if input is incorrect.
  // Returns true and fills gameboard if input is correct.

    bool tryToFillBoard();

    // String that informs what type of error in game start parameters
    QString invalidStartError;

    // User input seed or game
    std::string inputText;

    // Buttons accessible during game
    QPushButton *closeButton;
    QPushButton *resetButton;
    QPushButton *startOverButton;
    QPushButton *pauseButton;

    // Timer for timing game
    QTimer *timer;
    QLabel *timerLabel;

    // Sets the display text for the timer and updates elapsed seconds
    void updateTimer();

    // Seconds used in-game.
    unsigned int elapsedSeconds = 0;

    // Resets to start screen
    void resetGame();

    // Starts over current game
    void startOver();

    // Resumes paused game
    void resumeGame();
};
#endif // MAINWINDOW_HH
