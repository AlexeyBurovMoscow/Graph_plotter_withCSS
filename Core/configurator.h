#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <memory>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <Virtual/iplotbehavior.h>
#include <Core/utils.h>

namespace Core

{
    class Configurator
    {
    private:
        int m_min;
        int m_max;
        int m_delay;
        QString m_recordpath = "D:/";
        QString m_jsonpath;

        Visualization::Logic m_behavior = Visualization::Logic::Kinetic;
        Configurator(int min = -10, int max = 10, int delay = 1);
        ///pimpl
        class ConfiguratorPrivate;
        std::unique_ptr<ConfiguratorPrivate> confPrivate;

    public:
        ///getobject
        virtual ~Configurator();
        static Configurator& instance();

        ///interface
        void setMin(int min);
        void setMax(int max);
        void setDelay(int delay);
        void setBehavior(int logic);
        void setRecordPath(const QString &path);

        int getMax();
        int getMin();
        int getDelay();
        int getBehavior();
        QString getRecordPath() const;

        void setJsonPath(const QString &path);
        QString getJsonPath();



};
}
#endif // CONFIGURATOR_H
