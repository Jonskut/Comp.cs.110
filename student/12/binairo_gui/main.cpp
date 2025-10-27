/*
Binairo GUI

DESCRIPTION:

This program implements the Binairo game with a GUI.
The game features a board, where each square is either empty, zero, or one.

Board size can be adjusted by changing the variable NUMBER_OF_SYMBOLS
value in gameboard.hh, line 28.

The objective is to fill the empty squares according to the following rules:
 - Each row and column can have at most NUMBER_OF_SYMBOLS
   (default = 3) instances of the same number.
 - Each row and column can have at most two
   consecutive instances of the same number.

The game ends in victory
if the game grid is filled according to the aforementioned rules.

The program prevents additions that violate the
specified rules, but it is possible to reach a situation
where no further additions are possible.
The program validates the input provided by the user.

HOW TO PLAY:

Start screen:
Select gamemode (random/manual).

In the first option, the user is prompted for the seed of the random number
generator.

In the second option, the user is asked to input (2*NUMBER_OF_SYMBOLS)²
symbols (see gameboard.hh, line 28),of characters '0', '1', and ' '
(whitespace). Your input string will be validated for correctness.

When you are ready, press the button "Ready to play"!

In game:
You will be greeted by a board. The symbols on the initial board are dotted
to indicate that they cannot be changed.

Click a square on the gameboard. Clicking a non-dotted square will change
the symbol in the following pattern:
    empty --> zero  (hollow circle)
    zero  --> one   (solid circle)
    one   --> empty (empty square)

You are allowed to make an invalid move, but they will be flagged with a
red-border symbol.

You can pause the game, start over (timer won't reset), start a new game or
close the program.

If you correctly fill a board, you will go to an end screen that shows your
solve time. From there you can start a new game or close the program.

DESIGN CHOICES AND PROGRAM STRUCTURE

- gameboard (.hh/.cpp) contains the logic for how the gameboard works
- gameboardwidget is a custom widget that handles drawing the
  contents of the gameboard and handles mouse press events on the board.
- mainwindow contains the central widget and the whole gui is being controlled
  by mainwindow.
- utils has a couple useful methods
- gameoverdialog, invalidstartdialog, pausedialog are dialogs that have
  simple functionalities and are launched when certain conditions are met.

The design of this program is made to be as user-friendly and simple to use as
possible. It is robust while not feeling clunky and annoying.

 Written by
 Name: Jonatan Tevaniemi
 Student number: 150176680
 Username: cnjote
 E-Mail: jonatan.tevaniemi@tuni.fi

!!IMPORTANT!!
The features implemented in this program:

Minimum requirements:
    - All
Extra features:
    - Chips have been implemented as figures (10p.)
    - The game lets user make an erroneous addition,
      but it shows this error in a graphical way (as red border). (15 p.)
    - The game has a pause button (10 p.)
 */

#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
