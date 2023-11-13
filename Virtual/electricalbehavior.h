#ifndef ELECTRICALBEHAVIOR_H
#define ELECTRICALBEHAVIOR_H

#include <QString>
#include <QList>
#include <Virtual/iplotbehavior.h>

namespace Visualization
{
    class ElectricalBehavior : public IPlotBehavior
    {
    public:
        ElectricalBehavior();
        QList<QString> nameaxis();
};
}
#endif // ELECTRICALBEHAVIOR_H
