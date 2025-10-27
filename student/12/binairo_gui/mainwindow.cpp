#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawBoard()
{
    // Clear screen to make way for gameboard
    delete this->centralWidget();

    // Create a new central widget
    QWidget *newCentralWidget = new QWidget(this);

    boardWidget = new GameBoardWidget(board, this);

    // Create layout for the game
    QVBoxLayout *layout = new QVBoxLayout(newCentralWidget);

    // Scroll area is neceassary to suit many screen sizes and big boards
    boardWidget->setFixedSize(boardWidget->sizeHint());
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setWidget(boardWidget);

    // Add the scroll area to the layout
    layout->addWidget(scrollArea);

    // Create timer for timing game
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
    timerLabel = new QLabel("00:00", this);
    timerLabel->setFont(QFont("Arial", 16));
    timerLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    timerLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(timerLabel);

    // Create buttons
    closeButton = new QPushButton("Close", this);
    pauseButton = new QPushButton("Pause", this);
    resetButton = new QPushButton("New Game", this);
    startOverButton = new QPushButton("Start Over", this);

    connect(closeButton, &QPushButton::clicked,
            this, &MainWindow::close);
    connect(pauseButton, &QPushButton::clicked,
            this, &MainWindow::showPauseDialog);
    connect(resetButton, &QPushButton::clicked,
            this, &MainWindow::resetGame);
    connect(startOverButton, &QPushButton::clicked,
            this, &MainWindow::startOver);

    layout->addWidget(closeButton);
    layout->addWidget(pauseButton);
    layout->addWidget(resetButton);
    layout->addWidget(startOverButton);

    // Set the layout to the central widget
    newCentralWidget->setLayout(layout);
    setCentralWidget(newCentralWidget);

    // Start timer
    timer->start(1000);

    // Triggers when game is over
    connect(boardWidget, &GameBoardWidget::gameOver,
            this, &MainWindow::showGameOverDialog);

    boardWidget->update();
}


void MainWindow::showGameOverDialog()
{
    timer->stop();
    GameOverDialog dialog(this);
    dialog.setTime(timerLabel->text());
    connect(&dialog, &GameOverDialog::resetGameRequested,
            this, &MainWindow::resetGame);
    dialog.exec();
}

void MainWindow::showPauseDialog()
{
    timer->stop();
    PauseDialog dialog(this);
    // For pausing game
    connect(&dialog, &PauseDialog::resumeGame, this, &MainWindow::resumeGame);
    dialog.exec();
}

bool MainWindow::tryToFillBoard()
{
    inputText = ui->seedInputLineEdit->text().toStdString();

    // Check that an input option is checked
    if(!ui->randomButton->isChecked() && !ui->manualButton->isChecked())
    {
        invalidStartError = NOT_CHECKED;
        return false;
    }

    // Check for bad manual game input
    // Fills board if input is good
    if(ui->manualButton->isChecked())
    {
        if(inputText.length() != SIZE*SIZE)
        {
            invalidStartError = WRONG_LENGTH;
            return false;
        }
        for(char c : inputText)
        {
            if(c != '0' && c != '1' && c != ' ')
            {
                invalidStartError = WRONG_CHARACTERS;
                return false;
            }
        }

        std::string manualInputText = '"'+inputText+'"';

        if(!board.fill_from_input(manualInputText))
        {
            invalidStartError = BAD_INPUT;
            return false;
        }
    }

    // Check for bad seed
    // Fills board if seed is good
    if(!ui->manualButton->isChecked())
    {
        if(!utils::stoi_with_check(inputText))
        {
            invalidStartError = BAD_SEED_CHAR;
            return false;
        }
        unsigned int seed = utils::stoi_with_check(inputText);

        if(!board.fill_randomly(seed))
        {
            invalidStartError = BAD_SEED_LIST;
            return false;
        }
    }
    return true; // Good seed or input
}

void MainWindow::updateTimer()
{
    ++elapsedSeconds;
    int seconds = elapsedSeconds % 60;
    int minutes = elapsedSeconds / 60;

    QString displayText = QString("%1:%2")
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'));;
    timerLabel->setText(displayText);
}

void MainWindow::resetGame()
{
    // Close the current instance
    close();

    // Start another instance of the program
    QProcess::startDetached(QApplication::applicationFilePath());
}

void MainWindow::startOver()
{
    connect(this, &MainWindow::requestClearBoard, boardWidget,
            &GameBoardWidget::clearBoard);
    emit requestClearBoard();
}

void MainWindow::resumeGame()
{
    timer->start(1000);
}

void MainWindow::on_startButton_clicked()
{
    if(!tryToFillBoard())
    {
        InvalidStartDialog dialog(invalidStartError, this);
        dialog.exec();
    }
    else
    {
        drawBoard();
    }
}

void MainWindow::on_manualButton_clicked()
{
    ui->enterLabel->setText(MANUAL_HELPTEXT);
}


void MainWindow::on_randomButton_clicked()
{
    ui->enterLabel->setText(SEED_HELPTEXT);
}
