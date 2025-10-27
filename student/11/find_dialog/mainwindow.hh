#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <fstream>
#include <QMainWindow>
#include <cctype>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_fileLineEdit_editingFinished();

    void on_keyLineEdit_editingFinished();

    void on_findPushButton_clicked();

private:
    std::string toLower(const std::string& str);
    Ui::MainWindow *ui;
    std::string fileName;
    std::string keyWord;
    QString displayText;
};
#endif // MAINWINDOW_HH
