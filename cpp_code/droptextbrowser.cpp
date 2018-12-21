#include "droptextbrowser.h"


dropTextBrowser::dropTextBrowser(QWidget *parent): QTextBrowser (parent)
{
    setAcceptDrops(true);
    setMinimumHeight(25);
    setMaximumHeight(25);
}

dropTextBrowser::~dropTextBrowser()
{

}

void dropTextBrowser::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void dropTextBrowser::dragMoveEvent(QDragMoveEvent *event)
{
    event->setDropAction(Qt::CopyAction);
    event->accept();
}

void dropTextBrowser::dropEvent(QDropEvent *event)
{
    fileName = event->mimeData()->urls().first().toLocalFile();
    setText(fileName);
    emit fileNameChanged(fileName);
}
