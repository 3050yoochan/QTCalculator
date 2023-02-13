#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QButtonGroup digitButtonGroup;
    QButtonGroup operationButtonGroup;
    QButtonGroup unaryButtonGroup;

private slots :
    void digit_pressed(QAbstractButton * sender); //MAINWINDOW.cpp is CONNECTED WITH THIS!
    void on_pushButton_decimal_released();
    void unary_operation_pressed(QAbstractButton * sender);
    void on_pushButton_clear_released();
    void on_pushButton_equals_released();
    void binary_operation_pressed(QAbstractButton * sender);
};
#endif // MAINWINDOW_H
