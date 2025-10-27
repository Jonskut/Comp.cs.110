#include "invalidstartdialog.hh"
#include "ui_invalidstartdialog.h"

InvalidStartDialog::InvalidStartDialog(const QString& errorMessage,
                                       QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InvalidStartDialog)
{
    ui->setupUi(this);
    ui->errorMessageLabel->setText(errorMessage);
}

InvalidStartDialog::~InvalidStartDialog()
{
    delete ui;
}
