#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDoubleValidator> // Include validator header

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , focusedLineEdit(nullptr)
    , activeOperator(nullptr)
    , result(0)
{
    ui->setupUi(this);

    // Make result field read-only
    ui->lineEdit_result->setReadOnly(true);

    // Set validators to only allow numbers and decimal point
    QDoubleValidator *validator = new QDoubleValidator(this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEdit_firtsNum->setValidator(validator);
    ui->lineEdit_secondNum->setValidator(validator);

    // Loop to connect number buttons 0-9 to NumberClickHandler
    for (int i = 0; i <= 9; ++i) {
        QString buttonName = "pushButton_num" + QString::number(i);
        QPushButton *button = findChild<QPushButton *>(buttonName);
        if (button) {
            connect(button, &QPushButton::clicked, this, &MainWindow::NumberClickHandler);
        }
    }

    // Connect QLineEdit fields to lineFocusHandler() using selectionChanged()
    connect(ui->lineEdit_firtsNum, &QLineEdit::selectionChanged, this, &MainWindow::lineFocusHandler);
    connect(ui->lineEdit_secondNum, &QLineEdit::selectionChanged, this, &MainWindow::lineFocusHandler);

    // Connect operator buttons to operatorHandler
    connect(ui->pushButton_add, &QPushButton::clicked, this, &MainWindow::operatorHandler);
    connect(ui->pushButton_subtract, &QPushButton::clicked, this, &MainWindow::operatorHandler);
    connect(ui->pushButton_multiply, &QPushButton::clicked, this, &MainWindow::operatorHandler); // Multiply
    connect(ui->pushButton_divide, &QPushButton::clicked, this, &MainWindow::operatorHandler);

    // Connect calculate button to calculation function
    connect(ui->pushButton_calculate, &QPushButton::clicked, this, &MainWindow::calculate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Function to handle number button clicks and input into the focused QLineEdit
void MainWindow::NumberClickHandler()
{
    if (!focusedLineEdit) return; // Ensure a field is selected

    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        QString buttonText = button->text(); // Get the button's number
        focusedLineEdit->setText(focusedLineEdit->text() + buttonText);
    }
}

// Function to track which QLineEdit is in focus
void MainWindow::lineFocusHandler()
{
    QLineEdit *senderLineEdit = qobject_cast<QLineEdit *>(sender());
    if (senderLineEdit) {
        focusedLineEdit = senderLineEdit; // Update the focused QLineEdit
    }
}

// Function to ensure only one operator button is active at a time
void MainWindow::operatorHandler()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        if (activeOperator) {
            activeOperator->setStyleSheet(""); // Reset previous operator button
        }
        activeOperator = button;
        activeOperator->setStyleSheet("background-color: lightblue;"); // Highlight active operator
    }
}

// Function to perform the calculation based on the selected operator
void MainWindow::calculate()
{
    if (!activeOperator) {
        ui->lineEdit_result->setText("Error: No operator selected");
        return;
    }

    bool ok1, ok2;
    double num1 = ui->lineEdit_firtsNum->text().toDouble(&ok1);
    double num2 = ui->lineEdit_secondNum->text().toDouble(&ok2);

    if (!ok1 || !ok2) {
        ui->lineEdit_result->setText("Error: Invalid input");
        return;
    }

    double resultValue = 0;

    if (activeOperator == ui->pushButton_add) {
        resultValue = num1 + num2;
    } else if (activeOperator == ui->pushButton_subtract) {
        resultValue = num1 - num2;
    } else if (activeOperator == ui->pushButton_multiply) {
        resultValue = num1 * num2;
    } else if (activeOperator == ui->pushButton_divide) {
        if (num2 == 0) {
            ui->lineEdit_result->setText("Error: Divide by zero");
            return;
        }
        resultValue = num1 / num2;
    }

    ui->lineEdit_result->setText(QString::number(resultValue));
}

// Function to reset all values and clear fields
void MainWindow::on_pushButton_reset_clicked()
{
    // Clear all QLineEdit fields
    ui->lineEdit_firtsNum->clear();
    ui->lineEdit_secondNum->clear();
    ui->lineEdit_result->clear();

    // Reset stored variables
    focusedLineEdit = nullptr;
    activeOperator = nullptr;
    result = 0;

    // Reset operator button highlight to default
    QList<QPushButton*> operatorButtons = {
        ui->pushButton_add,
        ui->pushButton_subtract,
        ui->pushButton_multiply,
        ui->pushButton_divide
    };

    for (QPushButton* button : operatorButtons) {
        button->setStyleSheet(""); // Reset to default style
    }
}

// Function to handle decimal point input
void MainWindow::on_pushButton_decimal_clicked()
{
    if (!focusedLineEdit) return; // Ensure a field is selected

    QString currentText = focusedLineEdit->text();

    // Prevent multiple decimal points in the same number
    if (!currentText.contains('.')) {
        focusedLineEdit->setText(currentText + ".");
    }
}
