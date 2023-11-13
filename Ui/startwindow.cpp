#include "startwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QKeyEvent>
#include <Core/utils.h>
#include <Core/imagedepo.h>
#include <Ui/settingwindow.h>
#include <Ui/plotterwindow.h>
#include <QDebug>

struct Ui::StartWindow::StartWindowPrivate
{
    QVBoxLayout * mainlayout = nullptr;
    QGridLayout * gridlay = nullptr;
    QLabel * lbl_start = nullptr;
    QLabel * lbl_settings = nullptr;
    QPushButton * bn_exit = nullptr;
    QPushButton * bn_start = nullptr;
    QPushButton * bn_settings = nullptr;

    ///окна
    Ui::SettingWindow * settingWidget = nullptr;
    Ui::PlotterWindow * plotterWidget = nullptr;
};

Ui::StartWindow::StartWindow(QWidget *parent):
    QWidget(parent),
    privatewnd(std::make_unique<StartWindowPrivate>() )
{
    setWindowFlag(Qt::FramelessWindowHint);
    createGUI();
    connectGUI();
    ///css-style
    Core::Utils::setStyleSheet(":/Resources/Styles/StartWindow.css", this);

    ///event filter
    this->installEventFilter(this);
}

Ui::StartWindow::~StartWindow()
{}

void Ui::StartWindow::createGUI()
{
    Core::Utils::forceWndResolution(this);
    setObjectName("startwindow");
    privatewnd->mainlayout = new QVBoxLayout();
    privatewnd->gridlay = new QGridLayout();
    privatewnd->mainlayout->setMargin(0);
    privatewnd->mainlayout->setSpacing(0);
    privatewnd->gridlay->setMargin(0);
    privatewnd->gridlay->setSpacing(50);

    privatewnd->bn_exit = new QPushButton();
    privatewnd->bn_exit->setObjectName("ExitButton");
    privatewnd->bn_exit->setIcon(Core::ImageDepo::bnExitIco());
    privatewnd->bn_exit->setFixedSize(40,40);

    privatewnd->lbl_start = new QLabel(tr("Старт"));
    privatewnd->lbl_start->setObjectName("StartLabel");

    privatewnd->lbl_settings = new QLabel(tr("Настройки"));
    privatewnd->lbl_settings->setObjectName("SettingsLabel");

    privatewnd->bn_start = new QPushButton();
    privatewnd->bn_start->setIcon(Core::ImageDepo::bnStartIco());
    privatewnd->bn_start->setObjectName("StartButton");
    privatewnd->bn_start->setFixedSize(40,40);

    privatewnd->bn_settings = new QPushButton();
    privatewnd->bn_settings->setIcon(Core::ImageDepo::bnSettingsIco());
    privatewnd->bn_settings->setObjectName("SettingButton");
    privatewnd->bn_settings->setFixedSize(40,40);

    privatewnd->mainlayout->addWidget(privatewnd->bn_exit, 0, Qt::AlignRight | Qt::AlignTop);

    privatewnd->gridlay->addWidget(privatewnd->lbl_start,   0,0,1,1, Qt::AlignCenter);
    privatewnd->gridlay->addWidget(privatewnd->lbl_settings,0,1,1,1, Qt::AlignCenter);
    privatewnd->gridlay->addWidget(privatewnd->bn_start,    1,0,1,1, Qt::AlignCenter);
    privatewnd->gridlay->addWidget(privatewnd->bn_settings, 1,1,1,1, Qt::AlignCenter);
    privatewnd->mainlayout->addSpacing(200);
    privatewnd->mainlayout->addLayout(privatewnd->gridlay);
    privatewnd->mainlayout->addStretch(1);
    this->setLayout(privatewnd->mainlayout);
}

void Ui::StartWindow::connectGUI()
{
    QObject::connect(privatewnd->bn_exit, &QPushButton::clicked, qApp, &QApplication::exit);
    QObject::connect(privatewnd->bn_start, &QPushButton::clicked, this, &StartWindow::onStartClicked);
    QObject::connect(privatewnd->bn_settings, &QPushButton::clicked, this, &StartWindow::onSettingsClicked);
}

bool Ui::StartWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        auto keyEvent = static_cast<QKeyEvent*>(event);
        doProcessKeyPressing(keyEvent);

        return true;
    }

    return QObject::eventFilter(watched, event);
}

void Ui::StartWindow::doProcessKeyPressing(QKeyEvent *keyEvent)
{
    switch (keyEvent->key() )
    {
    case Qt::Key_1:
        qDebug() << "start";
        privatewnd->bn_start->animateClick();
        break;

    case Qt::Key_2:
        qDebug() << "settings";
        privatewnd->bn_settings->animateClick();
        break;
    }
}

void Ui::StartWindow::onStartClicked()
{
    privatewnd->plotterWidget = new PlotterWindow();
    connect(privatewnd->plotterWidget, &PlotterWindow::backToStartScreen, this, &StartWindow::onStartScreen);
    hide();
    privatewnd->plotterWidget->showNormal();
}

void Ui::StartWindow::onSettingsClicked()
{
    privatewnd->settingWidget = new SettingWindow();
    connect(privatewnd->settingWidget, &SettingWindow::backToStartScreen, this, &StartWindow::onStartScreen);
    hide();
    privatewnd->settingWidget->showNormal();
}

void Ui::StartWindow::onStartScreen(QWidget *invoker)
{
    qDebug() << "onStartScreen()";
    invoker->hide();
    delete invoker;
    showNormal();
}




