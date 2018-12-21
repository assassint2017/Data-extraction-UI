#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 连接信号&槽函数
    QObject::connect(ui->targetPathpushButton, &QPushButton::clicked, this, &MainWindow::ontargetPathClicked);
    QObject::connect(ui->storePathpushButton, &QPushButton::clicked, this, &MainWindow::onstorePathClicked);

    QObject::connect(ui->startDatecheckBox, &QCheckBox::toggled, this, &MainWindow::startDateToggled);
    QObject::connect(ui->endDatecheckBox, &QCheckBox::toggled, this, &MainWindow::endDateToggled);
    QObject::connect(ui->regioncheckBox, &QCheckBox::toggled, this, &MainWindow::regionToggled);

    QObject::connect(ui->startdateEdit, &QDateEdit::userDateChanged, this, &MainWindow::showStartDate);
    QObject::connect(ui->enddateEdit, &QDateEdit::userDateChanged, this, &MainWindow::showEndDate);

    QObject::connect(ui->extractpushButton, &QPushButton::clicked, this, &MainWindow::confirmdataExtract);

    // 初始禁用部分部件
    ui->startdateEdit->setEnabled(false);
    ui->enddateEdit->setEnabled(false);

    // 创建自定义可拖拽文件的文本显示器
    targetPathBrowser = new dropTextBrowser;
    QObject::connect(targetPathBrowser, &dropTextBrowser::fileNameChanged, this, &MainWindow::targetPathDrop);
    ui->horizontalLayout->insertWidget(1, targetPathBrowser);

    // 创建指示箭头
    startYearArrow = new indicatorArrow;
    startMonthArrow = new indicatorArrow;
    startDateArrow = new indicatorArrow;

    endYearArrow = new indicatorArrow;
    endMonthArrow = new indicatorArrow;
    endDateArrow = new indicatorArrow;

    // 创建lcd
    startYearLcd = new lcd;
    startMonthLcd = new lcd;
    startDateLcd = new lcd;

    endYearLcd = new lcd;
    endMonthLcd = new lcd;
    endDateLcd = new lcd;

    startYearLcd->setDigitCount(4);
    startYearLcd->setMaximumNumber(2100);
    startYearLcd->setMinimumNumber(1900);
    endYearLcd->setDigitCount(4);
    endYearLcd->setMaximumNumber(2100);
    endYearLcd->setMinimumNumber(1900);

    startMonthLcd->setDigitCount(2);
    startMonthLcd->setMaximumNumber(12);
    startMonthLcd->setMinimumNumber(1);
    endMonthLcd->setDigitCount(2);
    endMonthLcd->setMaximumNumber(12);
    endMonthLcd->setMinimumNumber(1);

    startDateLcd->setDigitCount(2);
    startDateLcd->setMaximumNumber(31);
    startDateLcd->setMinimumNumber(1);
    endDateLcd->setDigitCount(2);
    endDateLcd->setMaximumNumber(getMaxdate(QDate::currentDate().year(), QDate::currentDate().month()));
    endDateLcd->setMinimumNumber(1);

    // 初始化设置lcd显示器
    startYearLcd->display(1900);
    startMonthLcd->display(1);
    startDateLcd->display(1);

    endYearLcd->display(QDate::currentDate().year());
    endMonthLcd->display(QDate::currentDate().month());
    endDateLcd->display(QDate::currentDate().day());

    startYearLcd->setEnabled(false);
    startMonthLcd->setEnabled(false);
    startDateLcd->setEnabled(false);

    endYearLcd->setEnabled(false);
    endMonthLcd->setEnabled(false);
    endDateLcd->setEnabled(false);

    // 连接lcd和指示箭头之间的信号槽
    QObject::connect(startYearLcd, &lcd::add, startYearArrow, &indicatorArrow::onLcdadd);
    QObject::connect(startMonthLcd, &lcd::add, startMonthArrow, &indicatorArrow::onLcdadd);
    QObject::connect(startDateLcd, &lcd::add, startDateArrow, &indicatorArrow::onLcdadd);

    QObject::connect(startYearLcd, &lcd::sub, startYearArrow, &indicatorArrow::onLcdsub);
    QObject::connect(startMonthLcd, &lcd::sub, startMonthArrow, &indicatorArrow::onLcdsub);
    QObject::connect(startDateLcd, &lcd::sub, startDateArrow, &indicatorArrow::onLcdsub);

    QObject::connect(endYearLcd, &lcd::add, endYearArrow, &indicatorArrow::onLcdadd);
    QObject::connect(endMonthLcd, &lcd::add, endMonthArrow, &indicatorArrow::onLcdadd);
    QObject::connect(endDateLcd, &lcd::add, endDateArrow, &indicatorArrow::onLcdadd);

    QObject::connect(endYearLcd, &lcd::sub, endYearArrow, &indicatorArrow::onLcdsub);
    QObject::connect(endMonthLcd, &lcd::sub, endMonthArrow, &indicatorArrow::onLcdsub);
    QObject::connect(endDateLcd, &lcd::sub, endDateArrow, &indicatorArrow::onLcdsub);

    // 设置日期范围的槽函数
    QObject::connect(startYearLcd, &lcd::valueChanged, this, &MainWindow::onstartLcdValueChanged);
    QObject::connect(startMonthLcd, &lcd::valueChanged, this, &MainWindow::onstartLcdValueChanged);

    QObject::connect(endYearLcd, &lcd::valueChanged, this, &MainWindow::onendLcdValueChanged);
    QObject::connect(endMonthLcd, &lcd::valueChanged, this, &MainWindow::onendLcdValueChanged);

    // 同步日历和lcd的槽函数
    QObject::connect(startYearLcd, &lcd::valueChanged, this, &MainWindow::onLcdValueChanged);
    QObject::connect(startMonthLcd, &lcd::valueChanged, this, &MainWindow::onLcdValueChanged);
    QObject::connect(startDateLcd, &lcd::valueChanged, this, &MainWindow::onLcdValueChanged);

    QObject::connect(endYearLcd, &lcd::valueChanged, this, &MainWindow::onLcdValueChanged);
    QObject::connect(endMonthLcd, &lcd::valueChanged, this, &MainWindow::onLcdValueChanged);
    QObject::connect(endDateLcd, &lcd::valueChanged, this, &MainWindow::onLcdValueChanged);

    // 将自定义的lcd和指示箭头加入到主界面中
    ui->horizontalLayout_3->insertWidget(5, startYearLcd);
    ui->horizontalLayout_3->insertWidget(7, startYearArrow);
    ui->horizontalLayout_3->insertWidget(8, startMonthLcd);
    ui->horizontalLayout_3->insertWidget(10, startMonthArrow);
    ui->horizontalLayout_3->insertWidget(11, startDateLcd);
    ui->horizontalLayout_3->insertWidget(13, startDateArrow);

    ui->horizontalLayout_4->insertWidget(5, endYearLcd);
    ui->horizontalLayout_4->insertWidget(7, endYearArrow);
    ui->horizontalLayout_4->insertWidget(8, endMonthLcd);
    ui->horizontalLayout_4->insertWidget(10, endMonthArrow);
    ui->horizontalLayout_4->insertWidget(11, endDateLcd);
    ui->horizontalLayout_4->insertWidget(13, endDateArrow);

    // 创建地区编号表格
    regionEditer = new QTableWidget;

    QStringList header;
    header << "地区编码";

    regionEditer->setRowCount(4);
    regionEditer->setColumnCount(1);
    regionEditer->setColumnWidth(0, 370);
    regionEditer->setHorizontalHeaderLabels(header);
    regionEditer->setEnabled(false);

    ui->horizontalLayout_5->insertWidget(4, regionEditer);

    // 设置添加行按钮
    ui->addRowPushButton->setEnabled(false);
    QObject::connect(ui->addRowPushButton, &QPushButton::clicked, this, &MainWindow::addrow);

    // 设置删除选中行按钮
    ui->removeRowpushButton->setEnabled(false);
    QObject::connect(ui->removeRowpushButton, &QPushButton::clicked, this, &MainWindow::removerow);

    // 创建计时器
    timer = new QTime;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showStartDate(const QDate &startDate)
{
    startYearLcd->display(startDate.year());
    startMonthLcd->display(startDate.month());
    startDateLcd->display(startDate.day());
}

void MainWindow::showEndDate(const QDate &endDate)
{
    endYearLcd->display(endDate.year());
    endMonthLcd->display(endDate.month());
    endDateLcd->display(endDate.day());
}

void MainWindow::ontargetPathClicked()
{
    filePath = QFileDialog::getOpenFileName(this, "csv文件目录", ".");
    targetPathBrowser->setText(filePath);
}

void MainWindow::onstorePathClicked()
{
    if (!filePath.isEmpty())
    {
        QFileInfo fi(filePath);
        storePath = QFileDialog::getExistingDirectory(this, "保存路径", fi.absolutePath());
    }
    else
        storePath = QFileDialog::getExistingDirectory(this, "保存路径", ".");

    ui->storePathBrowser->setText(storePath);
}

void MainWindow::startDateToggled(bool toggled)
{
    ui->startdateEdit->setEnabled(toggled);
    startYearLcd->setEnabled(toggled);
    startMonthLcd->setEnabled(toggled);
    startDateLcd->setEnabled(toggled);

    if (toggled == false)
    {
        startYearLcd->display(1900);
        startMonthLcd->display(1);
        startDateLcd->display(1);
    }
    else
    {
        startYearLcd->display(ui->startdateEdit->date().year());
        startMonthLcd->display(ui->startdateEdit->date().month());
        startDateLcd->display(ui->startdateEdit->date().day());
    }
}

void MainWindow::endDateToggled(bool toggled)
{
    ui->enddateEdit->setEnabled(toggled);
    endYearLcd->setEnabled(toggled);
    endMonthLcd->setEnabled(toggled);
    endDateLcd->setEnabled(toggled);

    if (toggled == false)
    {
        endYearLcd->display(QDate::currentDate().year());
        endMonthLcd->display(QDate::currentDate().month());
        endDateLcd->display(QDate::currentDate().day());
    }
    else
    {
        endYearLcd->display(ui->enddateEdit->date().year());
        endMonthLcd->display(ui->enddateEdit->date().month());
        endDateLcd->display(ui->enddateEdit->date().day());
    }
}

void MainWindow::onstartLcdValueChanged()
{
    int year = static_cast<int>(startYearLcd->value());
    int month = static_cast<int>(startMonthLcd->value());

    int maxDate = getMaxdate(year, month);
    if (startDateLcd->value() > maxDate) startDateLcd->display(maxDate);

    startDateLcd->setMaximumNumber(getMaxdate(year, month));

}

void MainWindow::onendLcdValueChanged()
{
    int year = static_cast<int>(endYearLcd->value());
    int month = static_cast<int>(endMonthLcd->value());

    int maxDate = getMaxdate(year, month);

    if (endDateLcd->value() > maxDate) endDateLcd->display(maxDate);
    endDateLcd->setMaximumNumber(maxDate);
}

int MainWindow::getMaxdate(int year, int month)
{
    int maxDate = 0;
    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        maxDate = 31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        maxDate = 30;
        break;
    case 2:
        if (QDate::isLeapYear(year))
            maxDate = 29;
        else
            maxDate = 28;
        break;
    }
    return maxDate;
}

void MainWindow::onLcdValueChanged()
{
    ui->startdateEdit->setDate(QDate(
                                   static_cast<int>(startYearLcd->value()),
                                   static_cast<int>(startMonthLcd->value()),
                                   static_cast<int>(startDateLcd->value())
                                 ));
    ui->enddateEdit->setDate(QDate(
                                 static_cast<int>(endYearLcd->value()),
                                 static_cast<int>(endMonthLcd->value()),
                                 static_cast<int>(endDateLcd->value())
                                 ));
}

void MainWindow::regionToggled(bool toggled)
{
    regionEditer->setEnabled(toggled);
    ui->addRowPushButton->setEnabled(toggled);
    ui->removeRowpushButton->setEnabled(toggled);
}

void MainWindow::targetPathDrop(const QString &fileName)
{
    filePath = fileName;
}

void MainWindow::addrow()
{
    regionEditer->insertRow(regionEditer->rowCount());
}

void MainWindow::removerow()
{
    regionEditer->removeRow(regionEditer->currentRow());
}

void MainWindow::confirmdataExtract()
{
    if (filePath.isEmpty() || storePath.isEmpty())
    {
        QMessageBox::warning(this, "warning", "Path setting is not complete!!!");
        return;
    }
    else
    {
        QString terminalCode = ".\\dataExtraction.exe ";

        QFileInfo fi;
        fi.setFile(filePath);

        // 确定三个路径
        QString extDir = fi.fileName().replace(".gz", "-ext.csv").insert(0, '/').insert(0, storePath);
        QString summaryDir = fi.fileName().replace(".gz", "-summary.csv").insert(0, '/').insert(0, storePath);

        // 写入终端命令
        terminalCode = terminalCode + filePath + " " + extDir + " " + summaryDir + " ";

        // 确定两个日期
        if (ui->startDatecheckBox->isChecked() == false)
            startDate.setDate(1900, 1, 1);
        else
            startDate.setDate(ui->startdateEdit->date().year(), ui->startdateEdit->date().month(), ui->startdateEdit->date().day());

        if (ui->endDatecheckBox->isChecked() == false)
            endDate = QDate::currentDate();
        else
            endDate.setDate(ui->enddateEdit->date().year(), ui->enddateEdit->date().month(), ui->enddateEdit->date().day());

        // 如果终止日期早于起始日期，则需要进行报错
        if (startDate > endDate)
        {
            QMessageBox::warning(this, "warning", "date error!!!");
            return;
        }

        // 写入终端命令
        terminalCode = terminalCode + QString::number(startDate.year()) + " ";
        terminalCode = terminalCode + QString::number(startDate.month()) + " ";
        terminalCode = terminalCode + QString::number(startDate.day()) + " ";

        terminalCode = terminalCode + QString::number(endDate.year()) + " ";
        terminalCode = terminalCode + QString::number(endDate.month()) + " ";
        terminalCode = terminalCode + QString::number(endDate.day());

        // 确定地区编码
        if (ui->regioncheckBox->isChecked())
        {
            for (int i = 0; i < regionEditer->rowCount(); i++)
            {
                if (regionEditer->item(i, 0))
                {
                    terminalCode = terminalCode + " " + regionEditer->item(i, 0)->text();
                }
            }
        }
        else
        {
            if (ui->startDatecheckBox->isChecked() == false && ui->endDatecheckBox->isChecked() == false)
            {
                QMessageBox::warning(this, "warning", "Missing input!!!");
                return;
            }
        }

        // 确认要执行数据提取，禁用按钮防止二次点击
        ui->extractpushButton->setEnabled(false);

        // 创建数据提取线程
        dataThread = new dataExtractThread(terminalCode);

        // 连接槽函数
        QObject::connect(dataThread, &dataExtractThread::finished, this, &MainWindow::ondataExtractThreadFinished);

        // 开始提取数据
        dataThread->start();

        // 计时开始
        timer->start();
    }
}

void MainWindow::ondataExtractThreadFinished()
{
    // 提取完毕，弹出对话框提醒用户并显示所用时间
    char temp[20];
    sprintf(temp, "time: %.2f s", timer->elapsed() / 1000.0);
    QMessageBox::information(this, "info", temp);

    // 提取完毕，恢复按钮的使用权限
    ui->extractpushButton->setEnabled(true);
}
