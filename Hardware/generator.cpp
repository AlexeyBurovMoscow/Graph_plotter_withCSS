#include "generator.h"
#include <Core/configurator.h>
#include <ctime>
#include <QDebug>

Hard::Generator::Generator()
{
    qDebug() << "generator here";

    auto &core = Core::Configurator::instance();
    curvalue = 0;
    minvalue = core.getMin();
    maxvalue = core.getMax();
}

Hard::Generator &Hard::Generator::instance()
{
    static Generator generator;
    return generator;
}

int Hard::Generator::getRandValue()
{
    int difference = abs(maxvalue - (-minvalue));
    if(difference == 0)
        difference = abs(maxvalue);
    return curvalue = minvalue + rand() % difference;
}
