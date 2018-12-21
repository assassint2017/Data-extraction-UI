#ifndef DATAEXTRACTTHREAD_H
#define DATAEXTRACTTHREAD_H

#include <QThread>
#include <QString>

class dataExtractThread : public QThread
{
public:
    explicit dataExtractThread(QString ,QObject *parent = nullptr);
    ~dataExtractThread();

protected:
    virtual void run();

private:
    QString terminalCode;
};

#endif // DATAEXTRACTTHREAD_H
