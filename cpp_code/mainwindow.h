#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDate>
#include <QTime>
#include <QIcon>
#include <QDebug>
#include <QString>
#include <QFileInfo>
#include <QStringList>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "lcd.h"
#include "indicatorarrow.h"
#include "droptextbrowser.h"
#include "dataextractthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // 路径选择按钮槽函数
    void ontargetPathClicked();
    void onstorePathClicked();

    // 三个选择按钮槽函数
    void startDateToggled(bool);
    void endDateToggled(bool);
    void regionToggled(bool);

    // 数据提取按钮的槽函数
    void confirmdataExtract();

    // 显示时间的槽函数
    void showStartDate(const QDate&);
    void showEndDate(const QDate&);

    // 拖拽文件的槽函数
    void targetPathDrop(const QString &);

    // 添加行槽函数
    void addrow();

    // 添加删除行槽函数
    void removerow();

    // 指示箭头槽函数
    void onstartLcdValueChanged();
    void onendLcdValueChanged();

    // 同步lcd和日期设置的槽函数
    void onLcdValueChanged();

    // 提取数据线程结束的槽函数
    void ondataExtractThreadFinished();

    // 获取日期范围
    int getMaxdate(int, int);

    // 文件路径
    QString filePath;
    QString storePath;

    // 起始日期、终止日期
    QDate startDate, endDate;

    // 自定义的可拖拽文件的文本显示器
    dropTextBrowser *targetPathBrowser;

    // 指示箭头
    indicatorArrow *startYearArrow;
    indicatorArrow *startMonthArrow;
    indicatorArrow *startDateArrow;

    indicatorArrow *endYearArrow;
    indicatorArrow *endMonthArrow;
    indicatorArrow *endDateArrow;

    // 自定义的lcd数字显示器
    lcd *startYearLcd;
    lcd *startMonthLcd;
    lcd *startDateLcd;

    lcd *endYearLcd;
    lcd *endMonthLcd;
    lcd *endDateLcd;

    // 地区编号表格
    QTableWidget *regionEditer;

    // 计算数据提取时间的计时器
    QTime *timer;

    // 数据提取线程
    dataExtractThread *dataThread;
};

#endif // MAINWINDOW_H
