#include "Mocs/City.moc"

City::City (std::string name, int x, int y, QWidget * parent) :
    QWidget {parent},
    itsName {name},
    x {x},
    y {y}
{
    setGeometry(QRect(x, y, size+5, size+5));
    setMouseTracking (true);
}

bool City::operator== (City *city) {
    return itsName == city->getName();
}

void City::toggleColors (bool fTurnYellow) {
    if (fTurnYellow) {
        bgColor = Qt::yellow;
        textColor = Qt::black;
    } else {
        bgColor = (bgColor == Qt::black) ? Qt::green : Qt::black;
        textColor = (textColor == Qt::white) ? Qt::black : Qt::white;
    }

    update();
}

void City::addNeighbor (City *city) {
    bool fAlreadyExists {false};
    for (City *neighbor : neighbors) {
        if (city == neighbor) {
            fAlreadyExists = true;
        }
    }

    if (!fAlreadyExists) {
        neighbors.push_back(city);
    }
}



