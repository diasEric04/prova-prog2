#include "Mocs/Road.moc"

Road::Road (City *startC, City *endC, int distance, QWidget *parent) :
    QWidget {parent},
    cityStart(startC),
    cityEnd(endC),
    distance{distance}
{
    setFixedSize(900,900);
    move(15, 15);
}

void Road::toggleColor (bool allBlack) {
    if (allBlack && color == Qt::blue) {
        color = Qt::black;
        update();
        return;
    } else if (!allBlack) {
        color = (color == Qt::black) ? Qt::blue : Qt::black;
        update();
    }
}