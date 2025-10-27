#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

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
    void on_calculatePushButton_clicked();

    void on_spinBoxN_valueChanged(int arg1);

    void on_spinBoxG_valueChanged(int arg1);

    void on_spinBoxE_valueChanged(int arg1);

    void on_spinBoxP_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    unsigned int nScore;
    unsigned int gScore;
    unsigned int pScore;
    unsigned int eScore;
    unsigned int totalScore;
    unsigned int wGrade;
    unsigned int pGrade;
};
#endif // MAINWINDOW_HH
