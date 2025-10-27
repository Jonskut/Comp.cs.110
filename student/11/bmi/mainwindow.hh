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
    void on_weightLineEdit_textChanged(const QString &arg1);

    void on_heightLineEdit_textChanged(const QString &arg1);

    void on_countButton_clicked();

    void on_weightLineEdit_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::MainWindow *ui;
    double height = 0.0;
    double weight = 0.0;
    double BMI;
    QString displayText;
    void calculateBMI(double weight, double height);
    void calculateDisplayText(double BMI);
};
#endif // MAINWINDOW_HH
