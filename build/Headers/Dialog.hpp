#pragma once

#include <QObject>
#include <QDialog>
#include "City.hpp"
#include "Road.hpp"
#include <vector>

class Dialog final : public QDialog {
    Q_OBJECT
public:
    explicit Dialog (QWidget *parent = nullptr);
    void appendCity (City * __city);
    void appendRoad (Road * __road);
    City *findCity(std::string cityName) const;

private:
    std::vector<City*> cities;
    std::vector<Road*> roads;
};