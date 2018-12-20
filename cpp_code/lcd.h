#ifndef LCD_H
#define LCD_H

#include <QLCDNumber>
#include <QWheelEvent>

class lcd : public QLCDNumber
{
    Q_OBJECT
public:
    lcd();
    void setMaximumNumber(int);
    void setMinimumNumber(int);
signals:
    void add();
    void sub();

    void valueChanged();

protected:
    virtual void wheelEvent(QWheelEvent *event);
private:
    int maxNumber;
    int minNumber;
};

#endif // LCD_H
