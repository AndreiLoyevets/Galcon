#include "sources.h"


QColor IndexToColor(int index)
{
    switch(index)
    {
    case 0:
        return Qt::gray;
    case 1:
        return Qt::red;
    case 2:
        return Qt::green;
    case 3:
        return Qt::blue;
    case 4:
        return Qt::cyan;
    case 5:
        return Qt::magenta;
    case 6:
        return Qt::yellow;
    case 7:
        return QColor(128,0,0);
    case 8:
        return QColor(66,111,66);
    default:
        return Qt::gray;
    }
}
