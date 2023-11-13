#include "imagedepo.h"

#include <QPixmap>
#include <QIcon>
#include <QBitmap>
#include <QPainter>
#include <QObject>


QIcon const& Core::ImageDepo::bnExitIco()
{
    static QIcon bnExit_ico(QObject::tr(":/Resources/Images/exitIcon.png"));
    return bnExit_ico;
}

QIcon const& Core::ImageDepo::bnBackIco()
{
    static QIcon bnBack_ico(QObject::tr(":/Resources/Images/backIcon.png"));
    return bnBack_ico;
}

QIcon const& Core::ImageDepo::bnHelpIco()
{
    static QIcon bnHelp_ico(QObject::tr(":/Resources/Images/question.png"));
    return bnHelp_ico;
}

const QIcon& Core::ImageDepo::bnStartIco()
{
    static QIcon bnSTART_ico(QObject::tr(":/Resources/Images/power.png"));
    return bnSTART_ico;
}

const QIcon& Core::ImageDepo::bnSettingsIco()
{
    static QIcon bnSettings_ico(":/Resources/Images/settings.png");
    return bnSettings_ico;
}

const QIcon& Core::ImageDepo::bnApplyIco()
{
    static QIcon bnApply_ico(":/Resources/Images/ok.png");
    return bnApply_ico;
}

const QIcon &Core::ImageDepo::bnReportIco()
{
    static QIcon bnReport_ico(":/Resources/Images/RecToFile.png");
    return bnReport_ico;
}

const QIcon &Core::ImageDepo::bnPathIco()
{
    static QIcon bnPath_ico(":/Resources/Images/triplepoint.png");
    return bnPath_ico;
}
