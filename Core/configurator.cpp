#include "configurator.h"
#include <QDebug>

struct  Core::Configurator::ConfiguratorPrivate
{

};
Core::Configurator::Configurator(int min, int max, int delay)
                                : m_min(min), m_max(max), m_delay(delay)
{
    qDebug() << "configurator here";
}

Core::Configurator::~Configurator()
{

}

Core::Configurator &Core::Configurator::instance()
{
    static Configurator config;
    return config;
}

void Core::Configurator::setMin(int min)
{
    m_min = min;
}

void Core::Configurator::setMax(int max)
{
    m_max = max;
}

void Core::Configurator::setDelay(int delay)
{
    m_delay = delay;
}

int Core::Configurator::getBehavior()
{
    return m_behavior;
}

QString Core::Configurator::getRecordPath() const
{
    qDebug() << "getRecordPath() called";
    return m_recordpath;
}

void Core::Configurator::setJsonPath(const QString &path)
{
    m_jsonpath = path;
}

QString Core::Configurator::getJsonPath()
{
    qDebug() << "getJsonPath() <<" << m_jsonpath;
    return m_jsonpath;
}

int Core::Configurator::getMax()
{
    qDebug() << "max = " << m_max;
    return m_max;
}

int Core::Configurator::getMin()
{
    qDebug() << "min = " << m_min;
    return m_min;
}

int Core::Configurator::getDelay()
{
    qDebug() << "delay = " << m_delay;
    return m_delay;
}

void Core::Configurator::setBehavior(int logic)
                                    ///как указать, что мне нужен enum?
{
    qDebug() << "setBehavior() called";
    switch (logic) {
    case Visualization::Logic::Kinetic:
    {
        qDebug() << "plotter - kinetic";
        m_behavior = Visualization::Logic::Kinetic;
        break;
    }
    case Visualization::Logic::Thermo:
    {
        qDebug() << "plotter - thermo";
        m_behavior = Visualization::Logic::Thermo;
        break;
    }
    case Visualization::Logic::Electro:
    {
        qDebug() << "plotter - electro";
        m_behavior = Visualization::Logic::Electro;
        break;
    }
    default:
        break;
    }
}

void Core::Configurator::setRecordPath(const QString &path)
{
    qDebug() << "setRecordPath() called";
    m_recordpath = path;
}

