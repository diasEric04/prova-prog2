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
    void raiseCities (void);
    City *findCity(std::string cityName) const;
    Road *findRoad(std::string cityStartName, std::string cityEndName);
    void generateRoute ();

public slots:
    void cityClicked (City *__city);


private:
    std::vector<City *> getShortestRoute ();

    City *fstCity = nullptr;
    City *sndCity = nullptr;
    std::vector<City*> cities;
    std::vector<Road*> roads;
};