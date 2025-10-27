#include "mainwindow.hh"
#include "ui_mainwindow.h"

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

void MainWindow::on_fileLineEdit_editingFinished()
{
    fileName = ui->fileLineEdit->text().toStdString();
}


void MainWindow::on_keyLineEdit_editingFinished()
{
    keyWord = ui->keyLineEdit->text().toStdString();
}

void MainWindow::on_findPushButton_clicked()
{
    std::ifstream file(fileName);

    if (!file.is_open())
    {
        ui->textBrowser->setText("File not found");
        return;
    }
    if (keyWord.empty())
    {
        ui->textBrowser->setText("File found");;
        return;
    }

    std::string line;
    displayText = "Word not found";
    while (std::getline(file, line))
        {
            if (!ui->matchCheckBox->isChecked())
            {
                std::string keyWordLower = toLower(keyWord);
                std::string lineLower = toLower(line);
                if (lineLower.find(keyWordLower) != std::string::npos)
                {
                    displayText = "Word found";
                    break;
                }
            }
            else
            {
                if (line.find(keyWord) != std::string::npos)
                {
                    displayText = "Word found";
                    break;
                }
            }
        }

    ui->textBrowser->setText(displayText);
}

std::string MainWindow::toLower(const std::string &str)
{
    std::string result;
    result.reserve(str.length()); // Reserve space for the result

    for (char c : str)
    {
        result.push_back(std::tolower(c)); // Convert character to lowercase and add to result
    }

    return result;
}
