#include "thermodynamicalbehavior.h"

Visualization::ThermoDynamicalBehavior::ThermoDynamicalBehavior()
{

}

QList<QString> Visualization::ThermoDynamicalBehavior::nameaxis()
{
    QList<QString> list({"Температура", "Давление"});
    return list;
}
