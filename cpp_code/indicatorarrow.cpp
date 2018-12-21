#include "indicatorarrow.h"


indicatorArrow::indicatorArrow()
{
    QSize iconSize(20, 20);

    upButton = new QPushButton;
    downButton = new QPushButton;

    upButton->setStyleSheet("border-image: url(:/deactive/upArrow)");
    downButton->setStyleSheet("border-image: url(:/deactive/downArrow)");

    upButton->setEnabled(false);
    downButton->setEnabled(false);

    upButton->setIconSize(iconSize);
    downButton->setIconSize(iconSize);

    layout = new QVBoxLayout;

    layout->addWidget(upButton);
    layout->addWidget(downButton);

    setLayout(layout);

    setMinimumWidth(35);
    setMaximumWidth(35);

    // 创建局部的事件循环对象
    loop = new QEventLoop;
}

indicatorArrow::~indicatorArrow()
{

}

void indicatorArrow::onLcdadd()
{
    upButton->setStyleSheet("border-image: url(:/active/upArrow)");
    QTimer::singleShot(200, this, &indicatorArrow::onLcdAddTimeOut);

    if (loop->isRunning() == false)
        loop->exec();
}

void indicatorArrow::onLcdsub()
{
    downButton->setStyleSheet("border-image: url(:/active/downArrow)");
    QTimer::singleShot(200, this, &indicatorArrow::onLcdSubTimeOut);

    if (loop->isRunning() == false)
        loop->exec();
}

void indicatorArrow::onLcdAddTimeOut()
{
    if (loop->isRunning())
        loop->exit();
    upButton->setStyleSheet("border-image: url(:/deactive/upArrow)");
}

void indicatorArrow::onLcdSubTimeOut()
{
    if (loop->isRunning())
        loop->exit();
    downButton->setStyleSheet("border-image: url(:/deactive/downArrow)");
}
