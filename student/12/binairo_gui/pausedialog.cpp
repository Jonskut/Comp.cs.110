#include "pausedialog.hh"
#include "ui_pausedialog.h"

PauseDialog::PauseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PauseDialog)
{
    ui->setupUi(this);
}

PauseDialog::~PauseDialog()
{
    delete ui;
}

void PauseDialog::on_resumeButton_pressed()
{
    close();
}

void PauseDialog::closeEvent(QCloseEvent *event)
{
    emit resumeGame();
    QDialog::closeEvent(event);
}
