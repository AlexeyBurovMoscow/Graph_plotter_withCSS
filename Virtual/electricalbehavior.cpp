#include "electricalbehavior.h"


Visualization::ElectricalBehavior::ElectricalBehavior()
{

}

QList<QString> Visualization::ElectricalBehavior::nameaxis()
{
    QList<QString> list({"Напряжение", "Ток"});
    return list;
}
