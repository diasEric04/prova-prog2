#include "Mocs/Dialog.moc"
#include <algorithm>

Dialog::Dialog (QWidget *parent):
    QDialog {parent} 
{
    this->resize(900, 900);
}

void Dialog::appendCity (City *city) {
    this->cities.push_back(city);
}

void Dialog::appendRoad (Road *road) {
    this->roads.push_back(road);
}

City *Dialog::findCity (std::string cityName) const {
    for (auto city : cities) {
        if (city->getName() == cityName) {
            return city;
        }
    } return nullptr;
}