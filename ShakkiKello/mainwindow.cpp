#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>

// Constructor: Initializes the main window and game settings
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentMode(RAPID)
    , leftTime(300)
    , rightTime(300)
    , isLeftTurn(true)
    , gameStarted(false)
    , incrementLevel(0)
    , delayLevel(0)
    , prevLeftTime(300)
    , prevRightTime(300)
{
    ui->setupUi(this);

    // Timers for left and right players
    leftPlayerTimer = new QTimer(this);
    rightPlayerTimer = new QTimer(this);

    // Connect timers to their respective timeout handlers
    connect(leftPlayerTimer, &QTimer::timeout, this, &MainWindow::handleLeftPlayerTimer);
    connect(rightPlayerTimer, &QTimer::timeout, this, &MainWindow::handleRightPlayerTimer);

    // Connect start button to start function
    connect(ui->pushButton_start, &QPushButton::clicked, this, &MainWindow::on_pushButton_start_clicked);

    // Set initial UI state
    ui->label_announcer->setText("Choose game mode and other options, then press Start.");
    ui->pushButton_LeftPlayerButton->setEnabled(false);
    ui->pushButton_LeftPlayerButton->setStyleSheet("");
    ui->pushButton_RightPlayerButton->setEnabled(false);
    ui->pushButton_RightPlayerButton->setStyleSheet("");

    // Update timers and progress bars
    updateUI();

    // Ensure announcer label reflects initial values
    updateAnnouncer();
}

// Function to start the game when the start button is clicked
void MainWindow::on_pushButton_start_clicked()
{
    gameStarted = true;
    isLeftTurn = QRandomGenerator::global()->bounded(2); // Randomly choose player
    highlightCurrentPlayer();
    updateAnnouncer();
    updateUI();

    // Apply delay before the first turn starts
    QTimer::singleShot(delayLevel * 1000, this, [=]() {
        if (isLeftTurn) {
            leftPlayerTimer->start(1000);
        } else {
            rightPlayerTimer->start(1000);
        }
    });
}

// Toggles between RAPID and BLITZ modes
void MainWindow::on_pushButton_mode_clicked()
{
    if (gameStarted) return;    // Mode can only be changed before the game starts

    currentMode = (currentMode == RAPID) ? BLITZ : RAPID;

    // Set initial times based on mode
    leftTime = (currentMode == RAPID) ? 300 : 30;
    rightTime = (currentMode == RAPID) ? 300 : 30;

    prevLeftTime = leftTime;
    prevRightTime = rightTime;

    updateUI();
    updateAnnouncer();
}

// Cycle through predefined increment options
void MainWindow::on_pushButton_increment_clicked()
{
    if (gameStarted) return;

    static const QList<int> increments = {0, 1, 2, 3, 5, 10};
    int index = increments.indexOf(incrementLevel);
    incrementLevel = increments[(index + 1) % increments.size()];

    updateAnnouncer();
}

// Cycle through predefined delay options
void MainWindow::on_pushButton_delay_clicked()
{
    if (gameStarted) return;

    static const QList<int> delays = {0, 1, 5};
    int index = delays.indexOf(delayLevel);
    delayLevel = delays[(index + 1) % delays.size()];

    updateAnnouncer();
}

// Handles left player pressing their button
void MainWindow::on_pushButton_LeftPlayerButton_clicked()
{
    if (!gameStarted) return;

    leftTime = qMin(prevLeftTime, leftTime + incrementLevel);   // Apply increment
    prevLeftTime = leftTime;

    leftPlayerTimer->stop();
    rightPlayerTimer->stop();

    updateUI();
    switchTurn(); // Directly switch turns
}

// Handles right player pressing their button
void MainWindow::on_pushButton_RightPlayerButton_clicked()
{
    if (!gameStarted) return;

    rightTime = qMin(prevRightTime, rightTime + incrementLevel);    // Apply increment
    prevRightTime = rightTime;

    rightPlayerTimer->stop();
    leftPlayerTimer->stop();

    updateUI();
    switchTurn(); // Directly switch turns
}

// Handles left player timer
void MainWindow::handleLeftPlayerTimer()
{
    if (isLeftTurn && gameStarted) {
        leftTime--;
        updateUI();

        if (leftTime <= 0) {
            leftTime = 0;
            checkGameEnd();
            leftPlayerTimer->stop();
        }
    }
}

// Handles right player timer
void MainWindow::handleRightPlayerTimer()
{
    if (!isLeftTurn && gameStarted) {
        rightTime--;
        updateUI();

        if (rightTime <= 0) {
            rightTime = 0;
            checkGameEnd();
            rightPlayerTimer->stop();
        }
    }
}

// Switch turns between players
void MainWindow::switchTurn()
{
    isLeftTurn = !isLeftTurn;
    highlightCurrentPlayer();
    updateAnnouncer();

    leftPlayerTimer->stop();
    rightPlayerTimer->stop();

    QTimer::singleShot(delayLevel * 1000, this, [=]() {
        if (isLeftTurn) {
            leftPlayerTimer->start(1000);
        } else {
            rightPlayerTimer->start(1000);
        }
    });
}

// Highlights the active player
void MainWindow::highlightCurrentPlayer()
{
    if (!gameStarted) {
        ui->pushButton_LeftPlayerButton->setEnabled(false);
        ui->pushButton_LeftPlayerButton->setStyleSheet("");
        ui->pushButton_RightPlayerButton->setEnabled(false);
        ui->pushButton_RightPlayerButton->setStyleSheet("");
        return;
    }

    if (isLeftTurn) {
        ui->pushButton_LeftPlayerButton->setEnabled(true);
        ui->pushButton_LeftPlayerButton->setStyleSheet("background-color: green;");
        ui->pushButton_RightPlayerButton->setEnabled(false);
        ui->pushButton_RightPlayerButton->setStyleSheet("");
    } else {
        ui->pushButton_RightPlayerButton->setEnabled(true);
        ui->pushButton_RightPlayerButton->setStyleSheet("background-color: green;");
        ui->pushButton_LeftPlayerButton->setEnabled(false);
        ui->pushButton_LeftPlayerButton->setStyleSheet("");
    }
}

// Updates the counters and progressbars with player times
void MainWindow::updateUI()
{
    ui->lcdNumber_CountLeft->display(leftTime);
    ui->lcdNumber_CountRight->display(rightTime);

    int maxTime = (currentMode == RAPID) ? 300 : 30;
    ui->progressBar_left->setMaximum(maxTime);
    ui->progressBar_right->setMaximum(maxTime);

    ui->progressBar_left->setValue(leftTime);
    ui->progressBar_right->setValue(rightTime);
}

// Updates the announcer label with game status
void MainWindow::updateAnnouncer()
{
    if (!gameStarted) {
        ui->label_announcer->setText(QString(
        "Game not started. Choose mode and options, then press Start.\n" "Increment: %1s | Delay: %2s")
        .arg(incrementLevel)
        .arg(delayLevel)
        );
        return;
    }

    ui->label_announcer->setText(QString("Game started. %1 | Mode: %2 | Increment: %3s | Delay: %4s")
    .arg(isLeftTurn ? "Left's turn" : "Right's turn",
    (currentMode == RAPID) ? "RAPID" : "BLITZ",
    QString::number(incrementLevel),
    QString::number(delayLevel)
    )
    );
}

// Checks if the game has ended
void MainWindow::checkGameEnd()
{
    if (leftTime <= 0 || rightTime <= 0) {
        ui->label_announcer->setText(leftTime <= 0 ? "Right player wins!" : "Left player wins!");
        leftPlayerTimer->stop();
        rightPlayerTimer->stop();
        gameStarted = false;
        highlightCurrentPlayer();
    }
}
