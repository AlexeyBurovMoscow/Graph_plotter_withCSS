#include "settingwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QPalette>
#include <QString>
#include <QStringList>
#include <QComboBox>
#include <QMessageBox>
#include <QLineEdit>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QApplication>
#include <QByteArray>
#include <QTextStream>
#include <QJsonParseError>
#include <QJsonDocument>
#include <Core/utils.h>
#include <Core/imagedepo.h>
#include <Ui/maintitlewidget.h>
#include <Core/configurator.h>
#include <QDebug>

struct Ui::SettingWindow::SettingWindowPrivate
{
    QVBoxLayout * mainlayout = nullptr;
    QGridLayout * gridlayout = nullptr;
    QPushButton * bn_apply = nullptr;
    QPushButton * bn_path = nullptr;
    QSlider * slider = nullptr;
    QSpinBox * sb_min = nullptr;
    QSpinBox * sb_max = nullptr;
    Ui::MainTitleWidget * maintitle = nullptr;
    QLabel * min_lbl = nullptr;
    QLabel * max_lbl = nullptr;
    QLabel * discret_lbl = nullptr;
    QLabel * behavior_lbl = nullptr;
    QLabel * interval_lbl = nullptr;
    QLineEdit * path_edit = nullptr;
    QLabel * filesaver_lbl = nullptr;
    QComboBox * behavior_cb = nullptr;
    QString discret_str = "1 секунда";
    QHBoxLayout * path_lay = nullptr;
    QMessageBox * pmbx = nullptr;
    Core::JsSavePath_obj jsinfo;
};

Ui::SettingWindow::SettingWindow(QWidget *parent):
    QWidget(parent),
    privatewnd(std::make_unique<SettingWindowPrivate>() )
{
    setWindowFlag(Qt::FramelessWindowHint);
    createGUI();
    connectGUI();
    connectJSON();
    Core::Utils::setStyleSheet(":/Resources/Styles/SettingsWindow.css", this);
}


Ui::SettingWindow::~SettingWindow()
{
    delete privatewnd->pmbx;
}

void Ui::SettingWindow::createGUI()
{
    Core::Utils::forceWndResolution(this);
    QPalette lblpal;
    lblpal.setColor(QPalette::WindowText, QColor(Qt::red));

    privatewnd->min_lbl = new QLabel("Мин.значение");
    privatewnd->min_lbl->setPalette(lblpal);
    privatewnd->min_lbl->setStyleSheet(QString("font-size: %1px").arg(14));

    privatewnd->max_lbl = new QLabel("Макс.значение");
    privatewnd->max_lbl->setPalette(lblpal);
    privatewnd->max_lbl->setStyleSheet(QString("font-size: %1px").arg(14));

    privatewnd->discret_lbl = new QLabel("Частота обновления");
    privatewnd->discret_lbl->setPalette(lblpal);
    privatewnd->discret_lbl->setStyleSheet(QString("font-size: %1px").arg(14));

    privatewnd->behavior_lbl = new QLabel("График:");
    privatewnd->behavior_lbl->setPalette(lblpal);
    privatewnd->behavior_lbl->setStyleSheet(QString("font-size: %1px").arg(14));

    privatewnd->interval_lbl = new QLabel(privatewnd->discret_str);
    privatewnd->interval_lbl->setPalette(lblpal);
    privatewnd->interval_lbl->setStyleSheet(QString("font-size: %1px").arg(14));

    privatewnd->filesaver_lbl = new QLabel("Директория отчетов:");
    privatewnd->filesaver_lbl->setPalette(lblpal);
    privatewnd->filesaver_lbl->setStyleSheet(QString("font-size: %1px").arg(14));

    privatewnd->behavior_cb = new QComboBox();
    privatewnd->behavior_cb->setObjectName("BehaviorCombo");
    QStringList list({"Кинетика", "Термодинамика", "Электрика"});
    for(auto i : list)
    {
        privatewnd->behavior_cb->addItem(i);
    }

    setObjectName("settingswindow");
    this->setMinimumSize(800,600);

    privatewnd->path_lay = new QHBoxLayout();
    privatewnd->bn_path = new QPushButton();
    privatewnd->bn_path->setIcon(Core::ImageDepo::bnPathIco());
    privatewnd->bn_path->setObjectName("PathButton");

    privatewnd->mainlayout = new QVBoxLayout();
    privatewnd->mainlayout->setMargin(0);
    privatewnd->mainlayout->setSpacing(0);
    privatewnd->gridlayout = new QGridLayout();
    privatewnd->gridlayout->setMargin(10);
    privatewnd->gridlayout->setSpacing(30);
    privatewnd->bn_apply = new QPushButton();
    privatewnd->slider = new QSlider(Qt::Horizontal);
    privatewnd->sb_min = new QSpinBox();
    privatewnd->sb_min->setMinimum(-10);
    privatewnd->sb_min->setMaximum(-1);
    privatewnd->sb_max = new QSpinBox();
    privatewnd->sb_max->setMinimum(0);
    privatewnd->sb_max->setMaximum(10);
    privatewnd->maintitle = new Ui::MainTitleWidget("Настройки программы");
    privatewnd->bn_apply->setFixedSize(40,40);
    privatewnd->bn_apply->setIcon(Core::ImageDepo::bnApplyIco());
    privatewnd->bn_apply->setObjectName("ApplyButton");
    privatewnd->slider->setRange(1,5);
    privatewnd->slider->setTickInterval(1);
    privatewnd->slider->setTickPosition(QSlider::TicksBelow);
    privatewnd->slider->setObjectName("Slider");
    privatewnd->sb_min->setObjectName("SpinBoxMin");
    privatewnd->sb_max->setObjectName("SpinBoxMax");
    privatewnd->path_edit = new QLineEdit();
    privatewnd->path_edit->setObjectName("SourcePathEdit");

    privatewnd->path_lay->addWidget(privatewnd->bn_path);
    privatewnd->path_lay->addWidget(privatewnd->path_edit);

    privatewnd->gridlayout->addWidget(privatewnd->min_lbl,0,0,1,1, Qt::AlignCenter);
    privatewnd->gridlayout->addWidget(privatewnd->sb_min, 0,1,1,1,Qt::AlignCenter);
    privatewnd->gridlayout->addWidget(privatewnd->max_lbl,1,0,1,1,Qt::AlignCenter);
    privatewnd->gridlayout->addWidget(privatewnd->sb_max,1,1,1,1,Qt::AlignCenter);
    privatewnd->gridlayout->addWidget(privatewnd->discret_lbl,2,0,1,1,Qt::AlignCenter);
    privatewnd->gridlayout->addWidget(privatewnd->slider, 2,1,1,1, Qt::AlignCenter);
    privatewnd->gridlayout->addWidget(privatewnd->interval_lbl, 3,1,1,1, Qt::AlignCenter);
    privatewnd->gridlayout->addWidget(privatewnd->behavior_lbl,4,0,1,1, Qt::AlignCenter);
    privatewnd->gridlayout->addWidget(privatewnd->behavior_cb, 4,1,1,1, Qt::AlignCenter);
    privatewnd->gridlayout->addWidget(privatewnd->filesaver_lbl, 5,0,1,1, Qt::AlignCenter);
    privatewnd->gridlayout->addLayout(privatewnd->path_lay,5,1,1,1, Qt::AlignCenter);

    privatewnd->mainlayout->addWidget(privatewnd->maintitle);
    privatewnd->mainlayout->addLayout(privatewnd->gridlayout);
    privatewnd->mainlayout->addWidget(privatewnd->bn_apply, 5, Qt::AlignCenter);

    privatewnd->pmbx = new QMessageBox();
    privatewnd->pmbx->setText("О программе:");
    privatewnd->pmbx->setInformativeText("Автор: Буров А.В.");
    privatewnd->pmbx->setDefaultButton(QMessageBox::Ok);
    privatewnd->pmbx->move(  (width()-privatewnd->pmbx->width())/2,
                            (height()-privatewnd->pmbx->height())/2
                         );

    this->setLayout(privatewnd->mainlayout);
}

void Ui::SettingWindow::connectGUI()
{
    connect(privatewnd->maintitle->getBackButton(), &QPushButton::clicked, this, [this](bool){ emit backToStartScreen(this);});
    connect(privatewnd->bn_apply, &QPushButton::clicked, this, &SettingWindow::onApplyClicked);
    connect(privatewnd->bn_path, &QPushButton::clicked, this, &SettingWindow::onPathBnClicked);
    connect(privatewnd->maintitle->getHelpButton(), &QPushButton::clicked, this, &SettingWindow::showInfo);
    connect(privatewnd->slider, &QSlider::valueChanged, this, [this](int value){
        switch (value) {
        case 1:
            privatewnd->discret_str = "1 секунда";
            break;
        case 2:
            privatewnd->discret_str = "2 cекунды";
            break;
        case 3:
            privatewnd->discret_str = "3 cекунды";
            break;
        case 4:
            privatewnd->discret_str = "4 cекунды";
            break;
        case 5:
            privatewnd->discret_str = "5 cекунд";
            break;
        default:
            break;
        }
        privatewnd->interval_lbl->setText(privatewnd->discret_str);
    });
}

void Ui::SettingWindow::connectJSON()
{
    auto &core = Core::Configurator::instance();
    core.setJsonPath("/config/settings.json");
    if(isExistsJSON())
    {
        readJSON();
    }
    else
    {
        writeJSON();
    }
}

void Ui::SettingWindow::readJSON()
{
    auto &core = Core::Configurator::instance();

    if(isExistsJSON())
    {
        QFile file(QApplication::applicationDirPath() + core.getJsonPath());
        if (file.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&file);
            stream.setCodec("Windows-1251");

            auto fileData = QString(stream.readAll()).toUtf8();

            QJsonParseError error;
            QJsonDocument jsondoc = QJsonDocument::fromJson(fileData, &error);

            if (!jsondoc.isObject())
            {
                //qDebug() << "Parsing JSON object failed: " << error.errorString();
            }
            else
            {
                //qDebug() << "Creating root JSON object...";
                QJsonObject rootObj = jsondoc.object();
                QJsonObject infoObj = rootObj["PATH"].toObject();

                if (infoObj.isEmpty()) {
                    //qDebug() << "uartObj is null";
                }
                else
                {
                    privatewnd->jsinfo.savepath = infoObj["reportpath"].toString();
                    privatewnd->path_edit->setText(privatewnd->jsinfo.savepath);
                    core.setRecordPath(privatewnd->jsinfo.savepath);

                }
            }
        }
        file.close();
    }
}

void Ui::SettingWindow::writeJSON()
{
    auto &core = Core::Configurator::instance();
    QDir dir;
    dir.mkdir(QApplication::applicationDirPath() + "/config");
    QFile file(QApplication::applicationDirPath() + "/config/settings.json");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream writeStream(&file);
    QStringList strls;

    strls.push_back("{\n");
    strls.push_back("\"PATH\": {\n");
    strls.push_back("\"reportpath\":\"");
    strls.push_back(core.getRecordPath());
    strls.push_back("\"\n");
    strls.push_back("}\n");
    strls.push_back("}\n");

    for(auto i : strls)
    {
        writeStream << i;
    }

    file.close();
}

bool Ui::SettingWindow::isExistsJSON()
{
    auto &core = Core::Configurator::instance();
    return QFile::exists(QApplication::applicationDirPath() + core.getJsonPath());
}

void Ui::SettingWindow::onApplyClicked()
{
    Core::Configurator::instance().setMax(privatewnd->sb_max->value());
    Core::Configurator::instance().setMin(privatewnd->sb_min->value());
    Core::Configurator::instance().setDelay(privatewnd->slider->value());
    Core::Configurator::instance().setBehavior(privatewnd->behavior_cb->currentIndex());
    emit backToStartScreen(this);
}

void Ui::SettingWindow::onPathBnClicked()
{
    QFileDialog dlg;
    dlg.setFileMode(QFileDialog::Directory);
    Core::Configurator::instance().getRecordPath();
    if(dlg.exec())
    {
        QString path = dlg.directory().absolutePath();

        Core::Configurator::instance().setRecordPath(path);

        writeJSON();

        privatewnd->path_edit->setText(path);
    }
}

void Ui::SettingWindow::showInfo()
{
    privatewnd->pmbx->exec();
}



