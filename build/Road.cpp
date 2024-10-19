#include "Mocs/Road.moc"

Road::Road (City *startC, City *endC, int distance, QWidget *parent) :
    QWidget {parent},
    startX {startC->getX()},
    startY {startC->getY()},
    endX { endC->getX()},
    endY {endC->getY()}
{
    
}