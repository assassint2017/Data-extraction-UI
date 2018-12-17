#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDebug>
#include <QDate>
#include <QTime>

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
    void dataExtract();

    // 显示时间的槽函数
    void showStartDate(const QDate&);
    void showEndDate(const QDate&);

    // 文件路径
    QString filePath;
    QString storePath;

    // 起始日期、终止日期
    QDate startDate, endDate;
};

#endif // MAINWINDOW_H
