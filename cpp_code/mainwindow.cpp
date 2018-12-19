#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 连接信号的槽函数
    QObject::connect(ui->targetPathpushButton, &QPushButton::clicked, this, &MainWindow::ontargetPathClicked);
    QObject::connect(ui->storePathpushButton, &QPushButton::clicked, this, &MainWindow::onstorePathClicked);

    QObject::connect(ui->startDatecheckBox, &QCheckBox::toggled, this, &MainWindow::startDateToggled);
    QObject::connect(ui->endDatecheckBox, &QCheckBox::toggled, this, &MainWindow::endDateToggled);
    QObject::connect(ui->regioncheckBox, &QCheckBox::toggled, this, &MainWindow::regionToggled);

    QObject::connect(ui->startdateEdit, &QDateEdit::userDateChanged, this, &MainWindow::showStartDate);
    QObject::connect(ui->enddateEdit, &QDateEdit::userDateChanged, this, &MainWindow::showEndDate);

    QObject::connect(ui->extractpushButton, &QPushButton::clicked, this, &MainWindow::dataExtract);

    // 初始禁用部分部件
    ui->startdateEdit->setEnabled(false);
    ui->enddateEdit->setEnabled(false);
    ui->regiontextEdit->setEnabled(false);

    // 初始化设置lcd显示器
    ui->startYear->display("1900");
    ui->startMonth->display("1");
    ui->startDate->display("1");

    ui->endYear->display(QDate::currentDate().year());
    ui->endMonth->display(QDate::currentDate().month());
    ui->endDate->display(QDate::currentDate().day());

    // 创建自定义可拖拽文件的文本显示器
    targetPathBrowser = new dropTextBrowser;
    QObject::connect(targetPathBrowser, &dropTextBrowser::fileNameChanged, this, &MainWindow::targetPathDrop);
    ui->horizontalLayout->insertWidget(1, targetPathBrowser);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showStartDate(const QDate &startDate)
{
    ui->startYear->display(startDate.year());
    ui->startMonth->display(startDate.month());
    ui->startDate->display(startDate.day());
}

void MainWindow::showEndDate(const QDate &endDate)
{
    ui->endYear->display(endDate.year());
    ui->endMonth->display(endDate.month());
    ui->endDate->display(endDate.day());
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

    if (toggled == false)
    {
        ui->startYear->display(1900);
        ui->startMonth->display(1);
        ui->startDate->display(1);
    }
    else
    {
        ui->startYear->display(ui->startdateEdit->date().year());
        ui->startMonth->display(ui->startdateEdit->date().month());
        ui->startDate->display(ui->startdateEdit->date().day());
    }
}

void MainWindow::endDateToggled(bool toggled)
{
    ui->enddateEdit->setEnabled(toggled);
    if (toggled == false)
    {
        ui->endYear->display(QDate::currentDate().year());
        ui->endMonth->display(QDate::currentDate().month());
        ui->endDate->display(QDate::currentDate().day());
    }
    else
    {
        ui->endYear->display(ui->enddateEdit->date().year());
        ui->endMonth->display(ui->enddateEdit->date().month());
        ui->endDate->display(ui->enddateEdit->date().day());
    }
}

void MainWindow::regionToggled(bool toggled)
{
    ui->regiontextEdit->setEnabled(toggled);
}

void MainWindow::targetPathDrop(const QString &fileName)
{
    filePath = fileName;
}

void MainWindow::dataExtract()
{
    if (filePath.isEmpty() || storePath.isEmpty())
    {
        QMessageBox::warning(this, "warning", "Path setting is not complete!!!");
        return;
    }
    else
    {
        QTime time;
        time.start();

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
            QString region = ui->regiontextEdit->toPlainText();
            QStringList regions = region.split("\n");

            for (int i = 0; i < regions.size(); i++)
                terminalCode = terminalCode + " " + regions.at(i);
        }
        else
        {
            if (ui->startDatecheckBox->isChecked() == false && ui->endDatecheckBox->isChecked() == false)
            {
                QMessageBox::warning(this, "warning", "Missing input!!!");
                return;
            }
        }

        // 调用python脚本提取数据
        qDebug() << terminalCode << endl;
        system(terminalCode.toStdString().c_str());

        // 提取完毕，弹出对话框提醒用户并显示所用时间
        char temp[20];
        sprintf(temp, "time: %.2f s", time.elapsed() / 1000.0);
        QMessageBox::information(this, "info", temp);

        // 清空地区输入框
        ui->regiontextEdit->clear();
    }
}
