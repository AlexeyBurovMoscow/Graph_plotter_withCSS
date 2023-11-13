#ifndef MAINTITLEWIDGET_H
#define MAINTITLEWIDGET_H

#include <QLabel>
#include <memory>

class QResizeEvent;
class QPushButton;

namespace Ui
{

    class MainTitleWidget : public QLabel
    {
        Q_OBJECT

        struct PrivTitleData;
        std::unique_ptr<PrivTitleData> privData;

    public:
        explicit MainTitleWidget(const QString &label, QWidget *parent = nullptr);
        ~MainTitleWidget();

        QPushButton* getBackButton();
        QPushButton* getHelpButton();

    private:
        void createGUI();

    protected:
        void resizeEvent(QResizeEvent*event);

    };

}

#endif // MAINTITLEWIDGET_H
