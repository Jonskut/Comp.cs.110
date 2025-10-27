#include "gameoverdialog.hh"
#include "ui_gameoverdialog.h"

GameOverDialog::GameOverDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOverDialog)
{
    ui->setupUi(this);
}

GameOverDialog::~GameOverDialog()
{
    delete ui;
}

void GameOverDialog::setTime(const QString &time)
{
    QString displayText = "Time: "+ time;
    ui->timeLabel->setText(displayText);
}

void GameOverDialog::on_closeButton_clicked()
{
    QApplication::quit();
}


void GameOverDialog::on_newGameButton_clicked()
{
    emit resetGameRequested();
}

