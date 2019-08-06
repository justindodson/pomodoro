#include "timer.h"

Timer::Timer()
{

}

Timer::Timer(QLCDNumber *lcd, double duration)
{
    std::cout << "Hello" << std::endl;
    this->minutes = duration;
    this->output = lcd;
    this->timer = new QTimer(this);
}

void Timer::setupTimer(QLCDNumber *lcd, double duration)
{
    std::cout << "Hello" << std::endl;
    this->minutes = duration;
    this->output = lcd;
    this->timer = new QTimer(this);
}

void Timer::startTimer()
{
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(updateLCD()));

    this->seconds--;
    if(!pause){
        if(this->seconds <= 0)
        {
            this->seconds = 59;
            this->minutes--;
            if(this->minutes < 0)
            {
                this->pause = true;
            }
        }
    }
    this->timer->start(1000);

}

void Timer::pauseTimer()
{

}

void Timer::clearTimer()
{

}

// slots
void Timer::updateLCD()
{
    this->output->display(QString::number(this->minutes) + " : " + QString::number(this->seconds));
}
