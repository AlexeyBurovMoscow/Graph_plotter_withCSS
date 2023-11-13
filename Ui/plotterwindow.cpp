#include "plotterwindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <Core/utils.h>
#include <Ui/maintitlewidget.h>
#include <Core/utils.h>
#include <Core/imagedepo.h>
#include <Core/qcustomplot.h>
#include <Core/configurator.h>
#include <Core/filesaver.h>
#include <Hardware/generator.h>
#include <Virtual/speedbehavior.h>
#include <Virtual/electricalbehavior.h>
#include <Virtual/thermodynamicalbehavior.h>
#include <QList>
#include <QTimer>
#include <QDebug>

struct Ui::PlotterWindow::PlotterWindowPrivate
{
    QVBoxLayout * mainlayout = nullptr;
    QPushButton * bn_report = nullptr;
    Ui::MainTitleWidget * maintitle = nullptr;
    QGridLayout * gridlayout = nullptr;
    QLabel * reportbn_lbl = nullptr;
    QCustomPlot * plotter = nullptr;
    Visualization::IPlotBehavior * pb = nullptr;
    QMessageBox * pmbx = nullptr;
    QTimer timer;
};


Ui::PlotterWindow::PlotterWindow(QWidget *parent):
    QWidget(parent),
    privatewnd(std::make_unique<PlotterWindowPrivate>())
{
    Core::Configurator::instance().getMax();
    Core::Configurator::instance().getMin();
    Core::Configurator::instance().getDelay();
    setWindowFlag(Qt::FramelessWindowHint);
    setDataDefault();
    createGUI();
    connectGUI();
    connectHardWare();
    Core::FileSaver::instance();
    Core::Utils::setStyleSheet(":/Resources/Styles/PlotWindow.css", this);
}

Ui::PlotterWindow::~PlotterWindow()
{
    delete privatewnd->pb;
    delete privatewnd->pmbx;
}

void Ui::PlotterWindow::createGUI()
{
    Core::Utils::forceWndResolution(this);
    setObjectName("plotwindow");
    this->setMinimumSize(800,600);

    QPalette lblpal;
    lblpal.setColor(QPalette::WindowText, QColor(Qt::red));

    privatewnd->maintitle = new Ui::MainTitleWidget("Мониторинг параметров");
    privatewnd->mainlayout = new QVBoxLayout();

    privatewnd->reportbn_lbl = new QLabel("Создать отчет");
    privatewnd->reportbn_lbl->setPalette(lblpal);
    privatewnd->reportbn_lbl->setStyleSheet(QString("font-size: %1px").arg(14));

    privatewnd->plotter = new QCustomPlot();
    privatewnd->plotter->addGraph();
    privatewnd->plotter->yAxis->setRange(Core::Configurator::instance().getMin(), Core::Configurator::instance().getMax());

    switch (Core::Configurator::instance().getBehavior()) {
    case Visualization::Logic::Kinetic:
    {
        qDebug() << "Kinetic behavior setup";
        privatewnd->pb = new Visualization::SpeedBehavior();
        break;
    }
    case Visualization::Logic::Electro:
    {
        qDebug() << "Electro behavior setup";
        privatewnd->pb = new Visualization::ElectricalBehavior();
        break;
    }
    case Visualization::Logic::Thermo:
    {
        qDebug() << "Thermo behavior setup";
        privatewnd->pb = new Visualization::ThermoDynamicalBehavior();
        break;
    }
    default:
        break;
    }
    QList<QString> list = privatewnd->pb->nameaxis();
    privatewnd->plotter->xAxis->setLabel(list.at(0));
    privatewnd->plotter->yAxis->setLabel(list.at(1));
    privatewnd->plotter->setFixedHeight(650);

    privatewnd->bn_report = new QPushButton();
    privatewnd->bn_report->setFixedSize(150,40);
    privatewnd->bn_report->setIcon(Core::ImageDepo::bnReportIco());
    privatewnd->bn_report->setObjectName("ReportButton");

    privatewnd->gridlayout = new QGridLayout();
    privatewnd->gridlayout->setMargin(10);
    privatewnd->gridlayout->setSpacing(30);

    privatewnd->gridlayout->addWidget(privatewnd->reportbn_lbl,0,0,1,1, Qt::AlignCenter);
    privatewnd->gridlayout->addWidget(privatewnd->bn_report,0,1,1,1, Qt::AlignCenter);

    privatewnd->mainlayout->addWidget(privatewnd->maintitle);
    privatewnd->mainlayout->addWidget(privatewnd->plotter);
    privatewnd->mainlayout->addLayout(privatewnd->gridlayout);
    privatewnd->mainlayout->addStretch(1);
    privatewnd->mainlayout->setMargin(0);
    privatewnd->mainlayout->setSpacing(0);

    privatewnd->pmbx = new QMessageBox();
    privatewnd->pmbx->setText("О программе:");
    privatewnd->pmbx->setInformativeText("Автор: Буров А.В.");
    privatewnd->pmbx->setDefaultButton(QMessageBox::Ok);
    privatewnd->pmbx->move(  (width()-privatewnd->pmbx->width())/2,
                            (height()-privatewnd->pmbx->height())/2
                         );


    this->setLayout(privatewnd->mainlayout);
}

void Ui::PlotterWindow::connectGUI()
{
    connect(privatewnd->maintitle->getBackButton(), &QPushButton::clicked, this, [this](bool){ emit backToStartScreen(this);});
    connect(&privatewnd->timer, &QTimer::timeout, this, &PlotterWindow::updateData);
    connect(privatewnd->bn_report, &QPushButton::clicked, this, &PlotterWindow::onReportClicked);
    connect(privatewnd->maintitle->getHelpButton(), &QPushButton::clicked, this, &PlotterWindow::showInfo);
}

void Ui::PlotterWindow::connectHardWare()
{
    auto &core = Core::Configurator::instance();
    privatewnd->timer.setTimerType(Qt::TimerType::PreciseTimer);
    privatewnd->timer.start(1000 * core.getDelay());
}

void Ui::PlotterWindow::setDataDefault()
{
    coordX.resize(0);
    coordY.resize(0);
}

void Ui::PlotterWindow::showInfo()
{
     privatewnd->pmbx->exec();
}

void Ui::PlotterWindow::updateData()
{
    instantX++;
    instantY = Hard::Generator::instance().getRandValue();

    coordX.push_back(instantX);
    coordY.push_back(instantY);

    privatewnd->plotter->graph(0)->setData(coordX, coordY);

    if(!privatewnd->plotter->xAxis->range().contains(instantX))
    {
        privatewnd->plotter->xAxis->setRange(instantX-4,instantX+1);
    }
    privatewnd->plotter->replot();
}

void Ui::PlotterWindow::onReportClicked()
{
    Core::FileSaver::instance().createFile();
    Core::FileSaver::instance().write(coordX, coordY);
}
