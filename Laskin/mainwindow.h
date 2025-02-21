#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void NumberClickHandler();  // Handles number button clicks
    void lineFocusHandler();    // Handles which QLineEdit is in focus
    void operatorHandler();     // Ensures only one operator is active
    void calculate();           // Performs the calculation based on the selected operator
    void on_pushButton_reset_clicked();
    void on_pushButton_decimal_clicked();

private:
    Ui::MainWindow *ui;
    QLineEdit *focusedLineEdit; // Stores the currently focused QLineEdit
    QPushButton *activeOperator; // Stores the currently active operator button
    int result; // Stores calculation result
};

#endif // MAINWINDOW_H
