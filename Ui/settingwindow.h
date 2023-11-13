#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <memory>
#include <QWidget>

namespace Ui{
    class SettingWindow : public QWidget
    {
    Q_OBJECT
        public:
            explicit SettingWindow(QWidget *parent = nullptr);
            ~SettingWindow();
            void createGUI();
            void connectGUI();
            bool isExistsJSON();
    private:
            void connectJSON();
            void readJSON();
            void writeJSON();

    private:

    private:
        class SettingWindowPrivate;
        std::unique_ptr<SettingWindowPrivate> privatewnd;
    private slots:
        void onApplyClicked();
        void onPathBnClicked();
    public slots:
        void showInfo();
    signals:
        void backToStartScreen(QWidget *wdg);
};
}
#endif // SETTINGWINDOW_H
