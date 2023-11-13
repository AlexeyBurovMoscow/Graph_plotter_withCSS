#ifndef SPEEDBEHAVIOR_H
#define SPEEDBEHAVIOR_H

#include <QString>
#include <QList>
#include <Virtual/iplotbehavior.h>

namespace Visualization
{
    class SpeedBehavior : public IPlotBehavior
    {
    public:
        SpeedBehavior();
        QList<QString> nameaxis();
    };
}
#endif // SPEEDBEHAVIOR_H
