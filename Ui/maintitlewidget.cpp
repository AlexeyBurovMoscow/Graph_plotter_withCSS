#include "maintitlewidget.h"

#include <QPushButton>
#include <QResizeEvent>
#include <QApplication>

#include <Core/imagedepo.h>
#include <Core/utils.h>

struct Ui::MainTitleWidget::PrivTitleData
{
    QPushButton* bn_exit = nullptr;
    QPushButton* bn_back = nullptr;
    QPushButton* bn_help = nullptr;
};

Ui::MainTitleWidget::MainTitleWidget(QString const& label, QWidget *parent) : QLabel(parent),
    privData(std::make_unique<PrivTitleData>())
{
    setText(label);
    setObjectName("MainTitle");
    setAlignment(Qt::AlignCenter);

    createGUI();

    connect(privData->bn_exit, &QPushButton::clicked, [&] { qApp->exit(); });

    Core::Utils::setStyleSheet(":/Resources/Styles/MainTitle.css", this);
}

Ui::MainTitleWidget::~MainTitleWidget()
{
}

QPushButton *Ui::MainTitleWidget::getBackButton()
{
    return privData->bn_back;
}

QPushButton *Ui::MainTitleWidget::getHelpButton()
{
    return privData->bn_help;
}

void Ui::MainTitleWidget::createGUI()
{
    privData->bn_exit = new QPushButton(this);
    privData->bn_exit->setObjectName("bnExit");
    privData->bn_exit->setIcon(Core::ImageDepo::bnExitIco());
    privData->bn_exit->setFixedSize(28,28);

    privData->bn_back = new QPushButton(this);
    privData->bn_back->setObjectName("bnBack");
    privData->bn_back->setIcon(Core::ImageDepo::bnBackIco());
    privData->bn_back->setFixedSize(28,28);

    privData->bn_help = new QPushButton(this);
    privData->bn_help->setCheckable(true);
    privData->bn_help->setObjectName("bnHelp");
    privData->bn_help->setIcon(Core::ImageDepo::bnHelpIco());
    privData->bn_help->setFixedSize(28,28);
}

void Ui::MainTitleWidget::resizeEvent(QResizeEvent *event)
{
    privData->bn_exit->move(event->size().width() - privData->bn_exit->width(), 0);
    privData->bn_back->move(privData->bn_exit->pos().x() - privData->bn_back->width() - 2, 0);
    privData->bn_help->move(privData->bn_back->pos().x() - privData->bn_help->width() - 2, 0);
}
