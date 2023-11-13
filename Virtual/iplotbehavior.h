#pragma once
#include <QString>
#include <QList>

namespace Visualization
{
    enum Logic{Kinetic, Thermo, Electro};

    class IPlotBehavior
    {
    public:
        IPlotBehavior(){}
        virtual ~IPlotBehavior(){}

        virtual QList<QString> nameaxis() = 0;
    };
}
