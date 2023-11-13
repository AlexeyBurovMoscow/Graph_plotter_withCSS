#ifndef FILESAVER_H
#define FILESAVER_H

#include <memory>
#include <QString>

namespace Core {

class FileSaver
{
private:
    FileSaver();
    ///pimpl
    class FileSaverPrivate;
    std::unique_ptr<FileSaverPrivate> fsaverPrivate;
public:
    virtual ~FileSaver();
    ///get object
    static FileSaver& instance();

    ///interface
    void createFile();
    void write(QVector<double> &coordX, QVector<double> &coordY);
    void closeFile();
};

}



#endif // FILESAVER_H
