#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , leftTime(300)
    , rightTime(300)
    , isLeftTurn(true)
    , gameStarted(false)
    , currentMode(RAPID)
    , incrementLevel(0)
    , delayLevel(0)
    , prevLeftTime(300)
    , prevRightTime(300)
{
    ui->setupUi(this);
    leftPlayerTimer = new QTimer(this);
    rightPlayerTimer = new QTimer(this);

    connect(leftPlayerTimer, &QTimer::timeout, this, &MainWindow::handleLeftPlayerTimer);
    connect(rightPlayerTimer, &QTimer::timeout, this, &MainWindow::handleRightPlayerTimer);
    connect(ui->pushButton_start, &QPushButton::clicked, this, &MainWindow::on_pushButton_start_clicked);

    ui->label_announcer->setText("Choose game mode and other options, then press Start.");

    ui->pushButton_LeftPlayerButton->setEnabled(false);
    ui->pushButton_LeftPlayerButton->setStyleSheet("");
    ui->pushButton_RightPlayerButton->setEnabled(false);
    ui->pushButton_RightPlayerButton->setStyleSheet("");

    updateUI();
    updateAnnouncer();
}

void MainWindow::on_pushButton_start_clicked()
{
    gameStarted = true;
    isLeftTurn = QRandomGenerator::global()->bounded(2); // Randomly choose player
    highlightCurrentPlayer();
    updateAnnouncer();
    updateUI();

    QTimer::singleShot(delayLevel * 1000, this, [=]() {
        if (isLeftTurn) {
            leftPlayerTimer->start(1000);
        } else {
            rightPlayerTimer->start(1000);
        }
    });
}

void MainWindow::on_pushButton_mode_clicked()
{
    if (gameStarted) return; // Mode can only be changed before the game starts

    currentMode = (currentMode == RAPID) ? BLITZ : RAPID;

    if (currentMode == RAPID) {
        leftTime = rightTime = 300;
    } else {
        leftTime = rightTime = 30;
    }

    prevLeftTime = leftTime;
    prevRightTime = rightTime;

    updateUI();
    updateAnnouncer();
}

void MainWindow::on_pushButton_increment_clicked()
{
    if (gameStarted) return;

    static const QList<int> increments = {0, 1, 2, 3, 5, 10};
    int index = increments.indexOf(incrementLevel);
    incrementLevel = increments[(index + 1) % increments.size()];

    updateAnnouncer();
}

void MainWindow::on_pushButton_delay_clicked()
{
    if (gameStarted) return;

    static const QList<int> delays = {0, 1, 5};
    int index = delays.indexOf(delayLevel);
    delayLevel = delays[(index + 1) % delays.size()];

    updateAnnouncer();
}

void MainWindow::on_pushButton_LeftPlayerButton_clicked()
{
    if (!gameStarted) return;

    leftTime = qMin(prevLeftTime, leftTime + incrementLevel);
    prevLeftTime = leftTime;

    leftPlayerTimer->stop();
    rightPlayerTimer->stop();

    updateUI();
    QTimer::singleShot(delayLevel * 1000, this, &MainWindow::switchTurn);
}

void MainWindow::on_pushButton_RightPlayerButton_clicked()
{
    if (!gameStarted) return;

    rightTime = qMin(prevRightTime, rightTime + incrementLevel);
    prevRightTime = rightTime;

    rightPlayerTimer->stop();
    leftPlayerTimer->stop();

    updateUI();
    QTimer::singleShot(delayLevel * 1000, this, &MainWindow::switchTurn);
}

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

void MainWindow::updateAnnouncer()
{
    if (!gameStarted) {
        ui->label_announcer->setText("Game not started. Choose mode and options, then press Start.");
        return;
    }

    QString turnText = isLeftTurn ? "Left's turn" : "Right's turn";
    QString modeText = (currentMode == RAPID) ? "RAPID" : "BLITZ";
    QString incrementText = QString::number(incrementLevel);
    QString delayText = QString::number(delayLevel);

    QString statusMessage = QString("Game started. %1 | Mode: %2 | Increment: %3s | Delay: %4s")
                                .arg(turnText)
                                .arg(modeText)
                                .arg(incrementText)
                                .arg(delayText);

    ui->label_announcer->setText(statusMessage);
}

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
