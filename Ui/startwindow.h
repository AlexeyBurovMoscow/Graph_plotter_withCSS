#ifndef GUI_H
#define GUI_H

#include <memory>
#include <QWidget>
namespace Ui {
    class StartWindow: public QWidget
    {
    Q_OBJECT

        public:
            explicit StartWindow(QWidget *parent = nullptr);
            ~StartWindow();

            void createGUI();
            void connectGUI();

        private:
            ///pimpl
            class StartWindowPrivate;
            std::unique_ptr<StartWindowPrivate> privatewnd;

            virtual bool eventFilter(QObject* watched, QEvent* event) override;
            void doProcessKeyPressing(QKeyEvent *keyEvent);

    public slots:
            void onStartClicked();
            void onSettingsClicked();
            ///any of modes want start screen
            void onStartScreen(QWidget *invoker);
    };
}


#endif // GUI_H
