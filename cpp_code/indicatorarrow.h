#ifndef INDICATORARROW_H
#define INDICATORARROW_H

#include <QTimer>
#include <QEventLoop>
#include <QPushButton>
#include <QVBoxLayout>

class indicatorArrow : public QWidget
{
    Q_OBJECT
public:
    explicit indicatorArrow(QWidget *parent = nullptr);
    ~indicatorArrow();

    // 两个相应指示信号的槽函数
    void onLcdadd();
    void onLcdsub();

    // 两个相应定时器的槽函数
    void onLcdAddTimeOut();
    void onLcdSubTimeOut();
private:
    QPushButton *upButton;  // 上升箭头
    QPushButton *downButton;  // 下降箭头

    QVBoxLayout *layout;

    QEventLoop *loop;
};

#endif // INDICATORARROW_H
