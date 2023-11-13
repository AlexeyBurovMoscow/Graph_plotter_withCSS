#include "speedbehavior.h"


Visualization::SpeedBehavior::SpeedBehavior()
{

}

QList<QString> Visualization::SpeedBehavior::nameaxis()
{
    QList<QString> list({"Время", "Скорость"});
    return list;
}
