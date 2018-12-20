#include "lcd.h"

#include <QDebug>
lcd::lcd()
{

}

void lcd::setMaximumNumber(int number)
{
    maxNumber = number;
}

void lcd::setMinimumNumber(int number)
{
    minNumber = number;
}

void lcd::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0 && value() < maxNumber)
    {
        display(value() + 1);
        emit add();
        emit valueChanged();
    }
    if (event->delta() < 0 && value() > minNumber)
    {
        display(value() - 1);
        emit sub();
        emit valueChanged();
    }
}
