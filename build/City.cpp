#include "Mocs/City.moc"

City::City (std::string name, int x, int y, QWidget * parent) :
    QWidget {parent},
    itsName {name},
    x {x},
    y {y}
{}

