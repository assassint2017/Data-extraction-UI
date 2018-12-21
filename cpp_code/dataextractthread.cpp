#include "dataextractthread.h"

dataExtractThread::dataExtractThread(QString terminalCode)
{
    this->terminalCode = terminalCode;
}

dataExtractThread::~dataExtractThread()
{

}

void dataExtractThread::run()
{
    // 调用python脚本进行数据提取
    system(terminalCode.toStdString().c_str());
}
