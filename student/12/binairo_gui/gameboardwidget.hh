/* GameBoardWidget class
 * This widget is responsible for creating the actual UI part of the gameboard
 * and handling mouse events on the gameboard.
 * This widget is used in MainWindow.
 *
 * Written by:
 *  Name: Jonatan Tevaniemi
 *  Student number: 150176680
 *  Username: cnjote
 *  E-mail: jonatantevaniemi@tuni.fi
 *
 */
#ifndef GAMEBOARDWIDGET_HH
#define GAMEBOARDWIDGET_HH

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSize>

#include <gameboard.hh>
#include <utils.hh>
#include <iostream>

// Size of rectangle in gameboard
const int CELL_SIZE = 70;

namespace Ui
{
class GameBoardWidget;
}

class GameBoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameBoardWidget(GameBoard& board,
                             QWidget *parent = nullptr);
    ~GameBoardWidget();

    // Define size hint for widget, used for resizing etc.
    QSize sizeHint() const override;

public slots:
    // Makes all cells empty except for dotted ones (initial board)
    void clearBoard();

signals:
    // Emitted when the game is over, caught by MainWindow
    void gameOver();

protected:
    // Paints the board
    void paintEvent(QPaintEvent *event) override;

    // Determines what to do when mouse is pressed on the gameboard
    // (sets the new symbol). Emits gameOver if game is over.
    void mousePressEvent(QMouseEvent *event) override;

private:
    // Gameboard containing information about current game
    GameBoard& m_board;
    Ui::GameBoardWidget *ui;

    // Images displayed depending on the state of the game (gameboard symbols)
    const QImage zeroSolidImage = QImage(
                ":/image/Resources/circle-white.png");
    const QImage oneSolidImage = QImage(
                ":/image/Resources/circle-black.png");

    const QImage zeroDotImage = QImage(
                ":/image/Resources/circle-white-dot.png");
    const QImage oneDotImage = QImage(
                ":/image/Resources/circle-black-dot.png");

    const QImage zeroRedImage = QImage(
                ":/image/Resources/circle-white-red.png");
    const QImage oneRedImage = QImage(
                ":/image/Resources/circle-black-red.png");

    const QImage zeroRedDotImage = QImage(
                ":/image/Resources/circle-white-red-dot.png");
    const QImage oneRedDotImage = QImage(
                ":/image/Resources/circle-black-red-dot.png");

    QImage zeroImage;
    QImage oneImage;

    // For debugging and checking whether to print dotted image
    unsigned int printCount = 0;

    // Array containing dotted cells (cells in initial board, can't be changed)
    bool dottedCells[SIZE][SIZE];

    // Makes necessary checks to determine which image is displayed in each
    // cell. Options are, for ones and zeros: dotted, solid (normal), red,
    // and red dotted.
    // Returns image to be displayed in cell.
    QImage getImageForCell(int row, int col) const;
};

#endif // GAMEBOARDWIDGET_HH
