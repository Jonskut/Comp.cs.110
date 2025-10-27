#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);

    auto paletteMin = ui->lcdNumberMin->palette();
    auto paletteSec = ui->lcdNumberSec->palette();
    paletteMin.setColor(paletteMin.WindowText, Qt::blue);
    paletteSec.setColor(paletteSec.WindowText, Qt::red);
    ui->lcdNumberMin->setPalette(paletteMin);
    ui->lcdNumberSec->setPalette(paletteSec);

    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime()
{
    elapsedSeconds++;
    int seconds = elapsedSeconds % 60;
    ui->lcdNumberSec->display(seconds);

    int minutes = elapsedSeconds / 60;
    ui->lcdNumberMin->display(minutes);
}

void MainWindow::on_resetButton_clicked()
{
    timer->stop();
    elapsedSeconds = 0;
    timer->start(1000);
    ui->lcdNumberSec->display(0);
    ui->lcdNumberMin->display(0);
}

void MainWindow::on_startButton_clicked()
{
    timer->start(1000);

}


void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}

