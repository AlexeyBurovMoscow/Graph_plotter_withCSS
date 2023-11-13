#ifndef THERMODYNAMICALBEHAVIOR_H
#define THERMODYNAMICALBEHAVIOR_H

#include <QString>
#include <QList>
#include <Virtual/iplotbehavior.h>

namespace Visualization
{
    class ThermoDynamicalBehavior : public IPlotBehavior
    {
    public:
        ThermoDynamicalBehavior();
        QList<QString> nameaxis();
};
}
#endif // THERMODYNAMICALBEHAVIOR_H
