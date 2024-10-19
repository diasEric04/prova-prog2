#include "Dialog.cpp"
#include "Road.cpp"
#include "City.cpp"
#include <QApplication>
#include <QLayout>
#include <fstream>
#include <QDebug>
#include <sstream>
#include <algorithm>
#include <QLayout>

int main (int argc, char **argv) {
    QApplication app(argc, argv);

    Dialog *d = new Dialog();
    d->setWindowTitle("Eric Arruda Dias");

    std::ifstream file {"mapa-rs.txt"};

    std::string line;
    bool isCity = true;
    while (getline(file, line)) {
        std::istringstream ss {line};
        if (isCity) {
            std::string cidade, x, y;
            ss >> cidade >> x >> y;
            if (cidade == "") {
                isCity = false;
                continue;
            }
            City *newCity = new City {cidade, atoi(x.c_str()), atoi(y.c_str()), d};
            d->appendCity(newCity);
        } else {
            std::string cityStartName, cityEndName, distance;
            ss >> cityStartName >> cityEndName >> distance;
            City *cityStart = d->findCity(cityStartName);
            City *cityEnd = d->findCity(cityEndName);
            // qDebug() << cityStart->getName() << cityStart->getX() << cityStart->getY() << "|" << cityEnd->getName() << cityEnd->getX() << cityEnd->getY();
            Road *newRoad = new Road {cityStart, cityEnd, atoi(distance.c_str()), d};
            d->appendRoad(newRoad);
        }
    }

    d->show();

    return app.exec();
}