#include <QApplication>
#include "Ui/startwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ui::StartWindow gui;
    gui.show();
    return a.exec();
}
