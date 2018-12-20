#ifndef INDICATORARROW_H
#define INDICATORARROW_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QEventLoop>

class indicatorArrow : public QWidget
{
    Q_OBJECT
public:
    indicatorArrow();

    void onLcdadd();
    void onLcdsub();
private:
    QPushButton *upButton;  // 上升箭头
    QPushButton *downButton;  // 下降箭头

    QVBoxLayout *layout;
};

#endif // INDICATORARROW_H
