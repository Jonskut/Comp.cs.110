#include "gameboardwidget.hh"
#include "ui_gameboardwidget.h"

GameBoardWidget::GameBoardWidget(GameBoard& board,
                                 QWidget *parent) :
    QWidget(parent),
    m_board(board),
    ui(new Ui::GameBoardWidget)
{
    ui->setupUi(this);

    // Initialize the dotted cell status array with all cells set to false
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        for(unsigned int j = 0; j < SIZE; ++j)
        {
            dottedCells[i][j] = false;
        }
    }
}

GameBoardWidget::~GameBoardWidget()
{
    delete ui;
}

QSize GameBoardWidget::sizeHint() const
{
    return QSize(CELL_SIZE*SIZE+1, CELL_SIZE*SIZE+1);
}

void GameBoardWidget::clearBoard()
{
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        for(unsigned int j = 0; j < SIZE; ++j)
        {
            if(!dottedCells[i][j])
            {
                m_board.add_symbol(j, i, 'e');
            }
        }
    }
    update();
}

void GameBoardWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    // Draw the game board
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        for(unsigned int j = 0; j < SIZE; ++j)
        {
            QRect cellRect(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE);

            // Determine the image to be drawn based on cell dotting
            QImage image = getImageForCell(i, j);

            // Draw the symbol based on the game board state
            switch(m_board.get_board().at(i).at(j))
            {
            case ZERO:
                painter.fillRect(cellRect, utils::scaleImage(
                                     image, cellRect.size()));
                if(printCount < 2)
                {
                    dottedCells[i][j] = true;
                }
                break;
            case ONE:
                painter.fillRect(cellRect, utils::scaleImage(
                                     image, cellRect.size()));
                if(printCount < 2)
                {
                    dottedCells[i][j] = true;
                }
                break;
            case EMPTY:
                // Do nothing for empty cells
                break;
            }

            // Draw cell border
            painter.drawRect(cellRect);
        }
    }
    ++printCount;
}

QImage GameBoardWidget::getImageForCell(int row, int col) const
{
    // Determine the appropriate image based on whether the cell is dotted
    if(dottedCells[row][col])
    {
        if(m_board.get_board().at(row).at(col) == ZERO)
        {
            if(m_board.is_illegal_move(row, col))
            {
                return zeroRedDotImage;
            }
            return zeroDotImage;
        }
        else if(m_board.get_board().at(row).at(col) == ONE)
        {
            if(m_board.is_illegal_move(row, col))
            {
                return oneRedDotImage;
            }
            return oneDotImage;
        }
    }
    else if(m_board.is_illegal_move(row, col))
    {
        if(m_board.get_board().at(row).at(col) == ZERO)
        {
            return zeroRedImage;
        }
        else if(m_board.get_board().at(row).at(col) == ONE)
        {
            return oneRedImage;
        }
    }
    else
    {
        if(m_board.get_board().at(row).at(col) == ZERO)
        {
            return zeroSolidImage;
        }
        else if(m_board.get_board().at(row).at(col) == ONE)
        {
            return oneSolidImage;
        }
    }
    return QImage();
}


void GameBoardWidget::mousePressEvent(QMouseEvent *event)
{
    // Calculate the cell coordinates based on the mouse position
    int row = event->position().y() / CELL_SIZE;
    int col = event->position().x() / CELL_SIZE;

    // Ensure that the coordinates are within the valid range
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {

        qDebug() << "Cell at row" << row << "column" << col << "was pressed";

        // If the cell is dotted, do not perform any further action
        if(dottedCells[row][col])
        {
            return;
        }
        m_board.set_symbol(col, row);

        // Update the widget
        update();

        m_board.print();
        m_board.print_illegal_moves();
        if(m_board.is_game_over())
        {
            qDebug() << "WINWINWINWINWINW";
            emit gameOver();
        }
    }

    // Call the base class implementation to handle other mouse press events
    QWidget::mousePressEvent(event);
}
