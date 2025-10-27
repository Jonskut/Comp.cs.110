#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gradecalculator.hh"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxN->setMinimum(0);
    ui->spinBoxN->setMaximum(MAX_N_POINTS);

    ui->spinBoxG->setMinimum(0);
    ui->spinBoxG->setMaximum(MAX_G_POINTS);

    ui->spinBoxP->setMinimum(0);
    ui->spinBoxP->setMaximum(MAX_P_POINTS);

    ui->spinBoxE->setMinimum(0);
    ui->spinBoxE->setMaximum(5);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_spinBoxN_valueChanged(int arg1)
{
    nScore = arg1;
}


void MainWindow::on_spinBoxG_valueChanged(int arg1)
{
    gScore = arg1;
}


void MainWindow::on_spinBoxP_valueChanged(int arg1)
{
    pScore = arg1;
}


void MainWindow::on_spinBoxE_valueChanged(int arg1)
{
    eScore = arg1;
}


void MainWindow::on_calculatePushButton_clicked()
{
    wGrade = score_from_weekly_exercises(nScore, gScore);
    pGrade = score_from_projects(pScore);

    totalScore = calculate_total_grade(nScore, gScore, pScore, eScore);
    QString textToDisplay = "W-Score: " + QString::number(wGrade) + "\n" +
                            "P-Score: " + QString::number(pGrade) + "\n" +
                            "Total grade: " + QString::number(totalScore);
    ui->textBrowser->setText(textToDisplay);
}

