#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <iostream>
#include <QLCDNumber>
#include <QString>
#include <QTimer>
#include <QThread>

class Timer : public QObject
{
    Q_OBJECT

public:
    Timer();
    Timer(QLCDNumber *lcd, double duration);

    void setupTimer(QLCDNumber *output, double duration);


    void pauseTimer();
    void clearTimer();

public slots:
    void updateLCD();
    void startTimer();

private:
    QLCDNumber *output;
    QTimer *timer;

    bool pause = false;
    bool clear = false;

    double seconds = 0;
    double minutes;
};

#endif // TIMER_H
