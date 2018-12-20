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
}

void indicatorArrow::onLcdadd()
{
    upButton->setStyleSheet("border-image: url(:/active/upArrow)");

    QEventLoop loop;
    QTimer::singleShot(200, &loop, SLOT(quit()));
    loop.exec();

    upButton->setStyleSheet("border-image: url(:/deactive/upArrow)");
}

void indicatorArrow::onLcdsub()
{
    downButton->setStyleSheet("border-image: url(:/active/downArrow)");

    QEventLoop loop;
    QTimer::singleShot(200, &loop, SLOT(quit()));
    loop.exec();

    downButton->setStyleSheet("border-image: url(:/deactive/downArrow)");
}
