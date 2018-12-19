#ifndef DROPTEXTBROWSER_H
#define DROPTEXTBROWSER_H

#include <QTextBrowser>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QFile>
#include <QUrl>
#include <QMimeData>
#include <QString>

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
