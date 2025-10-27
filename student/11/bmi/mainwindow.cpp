#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->weightLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_weightLineEdit_textChanged);
    connect(ui->heightLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_heightLineEdit_textChanged);
    connect(ui->countButton, &QPushButton::clicked, this, &MainWindow::on_countButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_weightLineEdit_textChanged(const QString &arg1)
{
    weight = arg1.toInt();
}


void MainWindow::on_heightLineEdit_textChanged(const QString &arg1)
{
    height = arg1.toInt();
}


void MainWindow::on_countButton_clicked()
{
    calculateBMI(weight, height);
    calculateDisplayText(BMI);
}

void MainWindow::calculateBMI(double weight, double height)
{
    if(height <= 0 || weight <= 0)
    {
        BMI = 0;
    }
    else
    {
        double height_in_m = height/100.0;
        BMI = weight/(height_in_m*height_in_m);
    }

}

void MainWindow::calculateDisplayText(double BMI)
{
    if(BMI == 0.0)
    {
        displayText = " ";
    }
    else if(BMI < 18.5)
    {
        displayText = "Underweight";
    }
    else if(BMI > 25.0)
    {
        displayText = "Overweight";
    }
    else
    {
        displayText = "Normal range";
    }
    ui->infoTextBrowser->setText(displayText);

    if(BMI != 0.0)
    {
        ui->resultLabel->setText(QString::number(BMI));
    }
    else
    {
        ui->resultLabel->setText("Cannot count");
    }
}


