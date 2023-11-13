#include "filesaver.h"
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QStringList>
#include <QTextStream>
#include <QApplication>
#include <Core/configurator.h>
#include <QDebug>

struct Core::FileSaver::FileSaverPrivate
{
    bool opened = false;
    QString full_path;
    QString fname;
    QString basename = "savedData";
    QFile * mFile = nullptr;
};

Core::FileSaver::FileSaver():
    fsaverPrivate(std::make_unique<FileSaverPrivate>())
{
    qDebug() << "saver here";
}

Core::FileSaver::~FileSaver()
{}

Core::FileSaver &Core::FileSaver::instance()
{
    static FileSaver fsaver;
    return fsaver;
}

void Core::FileSaver::createFile()
{
    fsaverPrivate->opened = true;

    //QString path = QApplication::applicationDirPath() + "/reports";
    QString path = Core::Configurator::instance().getRecordPath() + "/reports";
    qDebug() << "report file created:" << path;
    QDir dir;
    dir.mkdir(path);

    fsaverPrivate->fname.clear();
    QString moment = QDateTime::currentDateTime().toString("yyyy_MM_dd____HH_m_ss");
    fsaverPrivate->fname = fsaverPrivate->basename + "_" + moment + ".txt";
    fsaverPrivate->full_path = path + "/" + fsaverPrivate->fname;

    if (!QFile::exists(path + fsaverPrivate->fname)) {
        fsaverPrivate->mFile = new QFile(fsaverPrivate->full_path);
    }
    fsaverPrivate->mFile->open(QIODevice::Append);
}

void Core::FileSaver::write(QVector<double> &coordX, QVector<double> &coordY)
{
    QString reportstr;

    QTextStream stream(fsaverPrivate->mFile);
    if (fsaverPrivate->mFile->isOpen())
    {

        int els = coordX.size();
        for(int i = 0; i < els; i++)
        {
            reportstr.push_back("(");
            reportstr.push_back(QString::number( coordX.at(i)));
            reportstr.push_back(",");
            reportstr.push_back(QString::number( coordY.at(i)));
            reportstr.push_back(")");
            reportstr.push_back("\n");
        }

        stream << reportstr;
    }

}

void Core::FileSaver::closeFile()
{
    if(fsaverPrivate->mFile->isOpen())
        fsaverPrivate->mFile->close();
}
