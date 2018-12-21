#ifndef DROPTEXTBROWSER_H
#define DROPTEXTBROWSER_H

#include <QUrl>
#include <QFile>
#include <QString>
#include <QMimeData>
#include <QDropEvent>
#include <QTextBrowser>
#include <QDragMoveEvent>
#include <QDragEnterEvent>

class dropTextBrowser : public QTextBrowser
{
    Q_OBJECT

public:
    dropTextBrowser();
    ~dropTextBrowser();

signals:
    void fileNameChanged(const QString &fileName);

protected:
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent *event);
    virtual void dropEvent(QDropEvent *event);

private:
    QString fileName;

};

#endif // DROPTEXTBROWSER_H
