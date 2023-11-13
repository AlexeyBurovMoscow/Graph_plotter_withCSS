#ifndef PLOTTERWINDOW_H
#define PLOTTERWINDOW_H

#include <memory>
#include <QWidget>

namespace Ui {
    class PlotterWindow : public QWidget
    {
        Q_OBJECT
    public:
        explicit PlotterWindow(QWidget * parent = nullptr);
        virtual ~PlotterWindow();
        void createGUI();
        void connectGUI();
        void connectHardWare();
        void setDataDefault();

    private:
        ///координаты на графике
        int instantX = 0;  ///мгновенные значения
        int instantY = 0;
                    ///контейнеры для отрисовки
        QVector<double> coordX;
        QVector<double> coordY;
    private:
        class PlotterWindowPrivate;
        std::unique_ptr<PlotterWindowPrivate> privatewnd;
    signals:
        void backToStartScreen(QWidget *wdg);
//        void s_coordX(QVector<double> &coordX);
//        void s_coordY(QVector<double> &coordY);
    public slots:
        void updateData();
        void onReportClicked();
        void showInfo();
};
}


#endif // PLOTTERWINDOW_H
