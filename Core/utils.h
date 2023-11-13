#pragma once

#include <QString>
#include <QStringList>


class QWidget;

namespace Core
{
    struct JsSavePath_obj
    {
        QString savepath;   ///произвольная информация храниящаяся в json
    };

    class Utils final
    {
    private:
        Utils() = delete;
        Utils(const Utils&) = delete;
        Utils& operator=(const Utils&) = delete;

    public:

        ///interface

        static void setStyleSheet(const QString& path, QWidget* widget);

        static void forceWndResolution(QWidget *wdg);
    };
}
