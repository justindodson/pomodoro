#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    ui->setupUi(this);
    this->audio = new QMediaPlayer;
    audio->setMedia(QUrl::fromLocalFile("/Volumes/TOSHIBA EXT/Code/cpp/PomodoroTimer/Resources/bell.mp3"));
    audio->setVolume(50);

    connect(ui->startBtn, SIGNAL(clicked()), this, SLOT(startBtnClicked()));
    connect(ui->pauseBtn, SIGNAL(clicked()), this, SLOT(pauseBtnClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// private slots

void MainWindow::startBtnClicked()
{
    // get the amount of time to set the timer to

    /*
     * 1.) validate the inputs
     * 2.) initialize the state
     */

    if(currentState != PAUSE)
    {
        if(validInput(ui->workDurationInput))
        {
            this->workMinutes = ui->workDurationInput->value();
        }
        else
        {
            //TODO: handle error for missing value
        }

        if(validInput(ui->breakDurationInput))
        {
            this->breakMinutes = ui->breakDurationInput->value();
        }
        else
        {
            //TODO: handle error for missing value
        }

    }

    this->currentState = RUN;
    this->isRunning = true;
    this->runTimer();
}

void MainWindow::updateLCD()
{
    this->workSeconds--;
    if(this->workSeconds <= 0)
    {
        this->workSeconds = 59;
        this->workMinutes--;

        if(this->workMinutes < 0)
        {
            // TODO: reset the timer here.
            this->audio->play();
            this->timer->stop();
            disconnect(this->timer, SIGNAL(timeout()), this, SLOT(updateLCD()));
            this->currentState = STOP;
            this->isRunning = false;
        }
    }


    // Formatting for the lcd Display
    if(this->workMinutes < 10)
    {

         if(this->workSeconds < 10)
         {
             ui->lcdNumber->display("0" + QString::number(this->workMinutes) + ":0"
                                    + QString::number(this->workSeconds));
         }
         else
         {
             ui->lcdNumber->display("0" + QString::number(this->workMinutes) + ":"
                                    + QString::number(this->workSeconds));
         }
    }
    else
    {

        if(this->workSeconds < 10)
        {
            ui->lcdNumber->display(QString::number(this->workMinutes) + ":0"
                                   + QString::number(this->workSeconds));
        }
        else
        {
            ui->lcdNumber->display(QString::number(this->workMinutes) + ":"
                                   + QString::number(this->workSeconds));
        }
    }


}

void MainWindow::pauseBtnClicked()
{
    this->currentState = PAUSE;
    this->timer->stop();
}

// private methods
void MainWindow::runTimer()
{
    this->timer = new QTimer(this); // TODO: remember to delete
    connect(this->timer, SIGNAL(timeout()), this, SLOT(updateLCD()));
    this->timer->start(100);
}

bool MainWindow::validInput(QSpinBox *input)
{
    if(input->value() > 0)
    {
        return true;
    }
    return false;
}













