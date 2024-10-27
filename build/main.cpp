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
#include <QFile>
#include <QMessageBox>

int main (int argc, char **argv) {
    QApplication app(argc, argv);

    Dialog *d = new Dialog();
    d->setWindowTitle("Eric Arruda Dias");

    QFile file ("mapa-rs.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return -1;

    QTextStream in (&file);

    bool isCity = true;
    while (!in.atEnd()) {
        QString line {in.readLine()};
        if (line.split(" ").length() != 3 && !line.isEmpty()) {
            QMessageBox::critical(d, "Erro", "Alguma linha no arquivo de input está incorreta");
            return -1;
        }
        std::istringstream ss {line.toStdString()};
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

            cityStart->addNeighbor(cityEnd);
            cityEnd->addNeighbor(cityStart);
            // qDebug() << cityStart->getName() << cityStart->getX() << cityStart->getY() << "|" << cityEnd->getName() << cityEnd->getX() << cityEnd->getY();
            Road *newRoad = new Road {cityStart, cityEnd, std::stoi(distance.c_str()), d};
            // qDebug() << cityStart->getName() << cityEnd->getName() << newRoad->getDistance();
            d->appendRoad(newRoad);
        }
    }

    d->raiseCities();
    d->show();

    return app.exec();
}