#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDoubleValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , activeLineEdit(nullptr)
    , selectedOperatorButton(nullptr)
    , retainOperator(false)
{
    ui->setupUi(this);

    // Set validators to allow decimal numbers
    QDoubleValidator *validator = new QDoubleValidator(this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEdit_1->setValidator(validator);
    ui->lineEdit_2->setValidator(validator);
    ui->lineEdit_3->setReadOnly(true);

    // Set focus to first input field
    activeLineEdit = ui->lineEdit_1;
    ui->lineEdit_1->setFocus();

    // Connect digit buttons using lambda slots
    for (int i = 0; i <= 9; ++i) {
        QString buttonName = "pushButton_" + QString::number(i);
        QPushButton *button = findChild<QPushButton *>(buttonName);
        if (button) {
            connect(button, &QPushButton::clicked, this, [this, button]() {
                if (activeLineEdit) {
                    activeLineEdit->setText(activeLineEdit->text() + button->text());
                }
                updateEnterButtonState();
            });
        }
    }

    // Connect decimal point button
    connect(ui->pushButton_decimal, &QPushButton::clicked, this, [this]() {
        if (activeLineEdit && !activeLineEdit->text().contains(".")) {
            activeLineEdit->setText(activeLineEdit->text() + ".");
        }
    });

    // Connect operator buttons
    connect(ui->pushButton_add, &QPushButton::clicked, this, [this]() { handleOperator(ui->pushButton_add, "+"); });
    connect(ui->pushButton_subtract, &QPushButton::clicked, this, [this]() { handleOperator(ui->pushButton_subtract, "-"); });
    connect(ui->pushButton_multiply, &QPushButton::clicked, this, [this]() { handleOperator(ui->pushButton_multiply, "*"); });
    connect(ui->pushButton_divide, &QPushButton::clicked, this, [this]() { handleOperator(ui->pushButton_divide, "/"); });

    // Connect clear and enter buttons
    connect(ui->pushButton_clear, &QPushButton::clicked, this, &MainWindow::clearFields);
    connect(ui->pushButton_enter, &QPushButton::clicked, this, &MainWindow::computeResult);

    // Connect backspace button
    connect(ui->pushButton_backspace, &QPushButton::clicked, this, &MainWindow::handleBackspace);

    // Connect line edits to track active field
    connect(ui->lineEdit_1, &QLineEdit::selectionChanged, this, [this]() { activeLineEdit = ui->lineEdit_1; });
    connect(ui->lineEdit_2, &QLineEdit::selectionChanged, this, [this]() { activeLineEdit = ui->lineEdit_2; });

    ui->pushButton_enter->setEnabled(false); // Disable enter button initially
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleOperator(QPushButton *button, const QString &op)
{
    if (selectedOperatorButton) {
        selectedOperatorButton->setStyleSheet(""); // Reset previous button style
    }

    if (selectedOperatorButton == button) {
        selectedOperator.clear();
        selectedOperatorButton = nullptr;
    } else {
        selectedOperator = op;
        selectedOperatorButton = button;
        selectedOperatorButton->setStyleSheet("background-color: #47b1e8; color: white;");
    }

    retainOperator = true;
    updateEnterButtonState();
}

void MainWindow::computeResult()
{
    if (selectedOperator.isEmpty()) return;

    float first = ui->lineEdit_1->text().toFloat();
    float second = ui->lineEdit_2->text().toFloat();
    float result = 0.0f;

    if (selectedOperator == "+") result = first + second;
    else if (selectedOperator == "-") result = first - second;
    else if (selectedOperator == "*") result = first * second;
    else if (selectedOperator == "/" && second != 0.0f) result = first / second;

    ui->lineEdit_3->setText(QString::number(result, 'g', 10)); // 'g' removes trailing zeros

    if (!retainOperator) {
        selectedOperator.clear();
        if (selectedOperatorButton) {
            selectedOperatorButton->setStyleSheet("");
            selectedOperatorButton = nullptr;
        }
    }

    retainOperator = false;
    ui->pushButton_enter->setEnabled(false);
}

void MainWindow::clearFields()
{
    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    selectedOperator.clear();
    retainOperator = false;
    if (selectedOperatorButton) {
        selectedOperatorButton->setStyleSheet("");
        selectedOperatorButton = nullptr;
    }
    ui->pushButton_enter->setEnabled(false);
}

void MainWindow::updateEnterButtonState()
{
    bool canPress = !ui->lineEdit_1->text().isEmpty() &&
                    !ui->lineEdit_2->text().isEmpty() &&
                    !selectedOperator.isEmpty();
    ui->pushButton_enter->setEnabled(canPress);
}

void MainWindow::handleBackspace()
{
    if (activeLineEdit && !activeLineEdit->text().isEmpty()) {
        QString text = activeLineEdit->text();
        text.chop(1); // Remove last character
        activeLineEdit->setText(text);
    }
}
