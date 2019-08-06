#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QSpinBox>
#include <QTimer>
#include <QMediaPlayer>


enum STATE
{
    RUN,
    STOP,
    PAUSE
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QMediaPlayer* audio;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startBtnClicked();
    void updateLCD();
    void pauseBtnClicked();

private:
    Ui::MainWindow *ui;

    QTimer* timer;

    STATE currentState;


    int workSeconds = 0;
    int workMinutes; // how many minutes the user inputs
    int breakSeconds = 0;
    int breakMinutes;

    bool isRunning = false;

    // private methods
    void runTimer();
    bool validInput(QSpinBox* input);
};

#endif // MAINWINDOW_H
