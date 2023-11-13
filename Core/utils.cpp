#include "utils.h"

#include <QFile>
#include <QDebug>
#include <QWidget>

void Core::Utils::setStyleSheet(const QString& path, QWidget* widget)
{
    QFile file(path);

    if (file.open(QIODevice::ReadOnly))
    {
        if (widget)
            widget->setStyleSheet(file.readAll());
        else
            qDebug() << "setStyleSheet: widget is nullptr";
    }
    else
        qDebug() << "setStyleSheet: file couldn't open at " + path;
}

void Core::Utils::forceWndResolution(QWidget *wdg)
{
    wdg->setGeometry(0,0,1024,768);
    wdg->setWindowFlag(Qt::FramelessWindowHint);
}
