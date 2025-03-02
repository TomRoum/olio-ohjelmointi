#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void on_pushButton_LeftPlayerButton_clicked();
    void on_pushButton_RightPlayerButton_clicked();
    void on_pushButton_mode_clicked();
    void on_pushButton_increment_clicked();
    void on_pushButton_delay_clicked();
    void on_pushButton_start_clicked();
    void handleLeftPlayerTimer();  // Handles countdown for left player
    void handleRightPlayerTimer(); // Handles countdown for right player

private:
    void switchTurn();
    void checkGameEnd();
    void updateAnnouncer();
    void highlightCurrentPlayer();
    void updateUI(); // Updates LCDs and progress bars

    Ui::MainWindow *ui;
    QTimer *leftPlayerTimer;
    QTimer *rightPlayerTimer;
    int leftTime;
    int rightTime;
    bool isLeftTurn;
    bool gameStarted;
    enum GameMode { RAPID, BLITZ };
    GameMode currentMode;
    int incrementLevel;
    int delayLevel;
    int prevLeftTime;
    int prevRightTime;
};

#endif // MAINWINDOW_H
