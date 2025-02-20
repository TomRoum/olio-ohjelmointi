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
    void handleOperator(QPushButton *button, const QString &op);
    void computeResult();
    void clearFields();
    void updateEnterButtonState();
    void handleBackspace(); // Added backspace functionality

private:
    Ui::MainWindow *ui;
    QString selectedOperator;
    QLineEdit *activeLineEdit;         // Tracks which field is active
    QPushButton *selectedOperatorButton; // Tracks currently active operator button
    bool retainOperator;               // Flag to retain operator after calculation
};

#endif // MAINWINDOW_H
