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

// MainWindow class manages the chess clock UI and game logic
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);     // Constructor: Initializes the main window

private slots:

    void on_pushButton_LeftPlayerButton_clicked();      // Handles button press for left player (switches turn)
    void on_pushButton_RightPlayerButton_clicked();     // Handles button press for right player (switches turn)
    void on_pushButton_mode_clicked();                  // Changes game mode (RAPID/BLITZ)
    void on_pushButton_increment_clicked();             // Cycles through increment time options
    void on_pushButton_delay_clicked();                 // Cycles through delay time options
    void on_pushButton_start_clicked();                 // Starts the game
    void handleLeftPlayerTimer();                       // Handles countdown for the left player's clock
    void handleRightPlayerTimer();                      // Handles countdown for the right player's clock

private:

    void switchTurn();                                  // Switches turn between left and right players
    void checkGameEnd();                                // Checks if the game has ended
    void updateAnnouncer();                             // Updates the announcer label with game status
    void highlightCurrentPlayer();                      // Highlights the active player in the UI
    void updateUI();                                    // Updates timers and progress bars in the UI

    Ui::MainWindow *ui;                                 // UI reference
    QTimer *leftPlayerTimer;                            // Timer for left player
    QTimer *rightPlayerTimer;                           // Timer for right player
    enum GameMode { RAPID, BLITZ };                     // Enum to define game modes
    GameMode currentMode;                               // Stores current game mode

    int leftTime;                                       // Remaining time for left player
    int rightTime;                                      // Remaining time for right player
    bool isLeftTurn;                                    // Indicates if it's the left player's turn
    bool gameStarted;                                   // Indicates if the game has started
    int incrementLevel;                                 // Increment time in seconds
    int delayLevel;                                     // Delay time in seconds
    int prevLeftTime;                                   // Tracks previous left time for increment logic
    int prevRightTime;                                  // Tracks previous right time for increment logic
};

#endif // MAINWINDOW_H
