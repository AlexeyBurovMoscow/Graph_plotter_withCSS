#ifndef IMAGEDEPO_H
#define IMAGEDEPO_H

class QPixmap;
class QImage;
class QIcon;

namespace Core
{
    /// Image deposit
    class ImageDepo
    {
    public:

       static const QIcon &bnExitIco();
       static const QIcon &bnBackIco();
       static const QIcon &bnHelpIco();  
       static const QIcon &bnStartIco();
       static const QIcon &bnSettingsIco();
       static const QIcon &bnApplyIco();
       static const QIcon &bnReportIco();
       static const QIcon &bnPathIco();
    };

}

#endif // IMAGEDEPO_H
