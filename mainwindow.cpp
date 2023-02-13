#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug> //KIND OF <stdio.h> in QT? THIS HEADER HELPS TO DEBUG WITH CONSOLE.
#include <QButtonGroup>

double firstNumber;
bool userIsTypingSecondNumber = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_add->setCheckable(true);

    ui->pushButton_subtract->setCheckable(true);

    ui->pushButton_multiply->setCheckable(true);

    ui->pushButton_divide->setCheckable(true);

    //MAINWINDOW CONNECTING NUMBER BUTTONS...
    //BY 'CONNECT'ING UIBUTTONS TO SLOT DIGIT_PRESSED().
    //USE QButtonGroup to minimize this text.

    digitButtonGroup.addButton(ui->pushButton_0);
    digitButtonGroup.addButton(ui->pushButton_1);
    digitButtonGroup.addButton(ui->pushButton_2);
    digitButtonGroup.addButton(ui->pushButton_3);
    digitButtonGroup.addButton(ui->pushButton_4);
    digitButtonGroup.addButton(ui->pushButton_5);
    digitButtonGroup.addButton(ui->pushButton_6);
    digitButtonGroup.addButton(ui->pushButton_7);
    digitButtonGroup.addButton(ui->pushButton_8);
    digitButtonGroup.addButton(ui->pushButton_9);
    connect(&digitButtonGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, &MainWindow::digit_pressed);

    operationButtonGroup.addButton(ui->pushButton_add);
    operationButtonGroup.addButton(ui->pushButton_subtract);
    operationButtonGroup.addButton(ui->pushButton_multiply);
    operationButtonGroup.addButton(ui->pushButton_divide);
    connect(&operationButtonGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, &MainWindow::binary_operation_pressed);

    unaryButtonGroup.addButton(ui->pushButton_plusMinus);
    unaryButtonGroup.addButton(ui->pushButton_percent);
    connect(&unaryButtonGroup, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked), this, &MainWindow::unary_operation_pressed);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed(QAbstractButton * sender)
{
    //qDebug() << "test";
    //THIS HOW TO PRINT ON THE CONSOLE. SIMILAR TO PRINTF.


    //SENDER IS RETURNING POINTER TO QPUSHBUTTON.
    //TEXT FROM THE BUTTON.
    QPushButton * button = (QPushButton*)sender;
    //ui->label->setText(button->text());
    //labelNumber is for saving label's Number.
    //labelNumber_ConvertForQString is QString variable, for setting texts at label settext. LINE54
    double labelNumber;
    QString labelNumber_ConvertForQString;

    if((ui->pushButton_add->isChecked() || ui->pushButton_subtract->isChecked() ||
            ui->pushButton_multiply->isChecked() || ui->pushButton_divide->isChecked()) && (!userIsTypingSecondNumber))
    {
        labelNumber = button->text().toDouble();
        userIsTypingSecondNumber = true;
        labelNumber_ConvertForQString = QString::number(labelNumber,'g',15); //g,15??
    }
    else
    {
        if(ui->label->text().contains('.') && button->text() == "0")
        {
            labelNumber_ConvertForQString = ui->label->text() + button->text();
        }
        else
        {
            labelNumber = (ui->label->text() + button->text()).toDouble();
            labelNumber_ConvertForQString = QString::number(labelNumber,'g',15);
        }
    }

    ui->label->setText(labelNumber_ConvertForQString);
}

//AUTOMATICALLY CONNECTED WITH THE MAINWINDOW UI BY PRESSING BUTTON AT MAINWINDOW -> BUTTON RIGHT CLICK
//->GO TO SLOT -> BUTTON RELEASED

void MainWindow::on_pushButton_decimal_released()
{
    //APPEARS DECIAMAL IN LABEL.
    ui->label->setText(ui->label->text() + ".");
}

//DEFINE AT MAINWINDOW.h FIRST
void MainWindow::unary_operation_pressed(QAbstractButton * sender)
{
    QPushButton * button = (QPushButton*)sender; //THIS TAKES EVERY BUTTON EVENT? Nope. Only defined by slot @ top.
    double labelNumber;
    QString labelNumber_ConvertForQString;

    if(button->text() == "+/-")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * -1;
        labelNumber_ConvertForQString = QString::number(labelNumber,'g',15);
        ui->label->setText(labelNumber_ConvertForQString);
    }

    else if(button->text() == "%")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * 0.01;
        labelNumber_ConvertForQString = QString::number(labelNumber,'g',15);
        ui->label->setText(labelNumber_ConvertForQString);
    }
}

//THE DIFFERENCE BETWEEN PRESSED AND RELEASED :
//PRESSED : WHEN YOU PRESS THE MOUSE BUTTON
//RELEASED : WHEN YOU PRESS AND TAKE YOUR FINGER OFF AT THE MOUSE BUTTON

void MainWindow::on_pushButton_clear_released() //"C"
{
    userIsTypingSecondNumber = false;
    ui->label->setText("0");
}

void MainWindow::on_pushButton_equals_released() //"="
{
    double labelNumber, secondNumber;
    QString labelNumber_ConvertForQString;

    secondNumber = ui->label->text().toDouble();

    if(ui->pushButton_add->isChecked())
    {
        labelNumber = firstNumber + secondNumber;
        labelNumber_ConvertForQString = QString::number(labelNumber,'g',15);
        ui->label->setText(labelNumber_ConvertForQString);
        operationButtonGroup.setExclusive(false);
        operationButtonGroup.checkedButton()->setChecked(false);
        operationButtonGroup.setExclusive(true);
    }
    else if(ui->pushButton_subtract->isChecked())
    {
        labelNumber = firstNumber - secondNumber;
        labelNumber_ConvertForQString = QString::number(labelNumber,'g',15);
        ui->label->setText(labelNumber_ConvertForQString);
        operationButtonGroup.setExclusive(false);
        operationButtonGroup.checkedButton()->setChecked(false);
        operationButtonGroup.setExclusive(true);
    }
    else if(ui->pushButton_multiply->isChecked())
    {
        labelNumber = firstNumber * secondNumber;
        labelNumber_ConvertForQString = QString::number(labelNumber,'g',15);
        ui->label->setText(labelNumber_ConvertForQString);
        operationButtonGroup.setExclusive(false);
        operationButtonGroup.checkedButton()->setChecked(false);
        operationButtonGroup.setExclusive(true);
    }
    else if(ui->pushButton_divide->isChecked())
    {
        labelNumber = firstNumber / secondNumber;
        labelNumber_ConvertForQString = QString::number(labelNumber,'g',15);
        ui->label->setText(labelNumber_ConvertForQString);
        operationButtonGroup.setExclusive(false);
        operationButtonGroup.checkedButton()->setChecked(false);
        operationButtonGroup.setExclusive(true);
    }

    userIsTypingSecondNumber = false;

}

void MainWindow::binary_operation_pressed(QAbstractButton * sender)
{
    QPushButton * button = (QPushButton*)sender;

    firstNumber = ui->label->text().toDouble();
    button->setChecked(true);
}
