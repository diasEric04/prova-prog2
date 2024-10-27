#pragma once

#include "City.hpp"
#include <string>
#include <QPainter>
#include <QWidget>
#include <cmath>

class Road final : public QWidget {
    Q_OBJECT
    friend class Dialog;
public: 
    Road (City *__cityStart, City *__cityEnd, int __kmDistance, QWidget * parent = nullptr);

    inline void paintEvent (QPaintEvent *event) override {
        QPainter painter(this);
        QPen pen (color);
        pen.setWidth(3);
        painter.setPen(pen);
        painter.setBrush(color);
        painter.drawLine(getStartX(), getStartY(), getEndX(), getEndY()); 
    }

    inline constexpr int getStartX (void) const noexcept { return cityStart->getX(); }
    inline constexpr int getStartY (void) const noexcept { return cityStart->getY(); }
    inline constexpr int getEndX (void) const noexcept { return cityEnd->getX(); }
    inline constexpr int getEndY (void) const noexcept { return cityEnd->getY(); }
    inline constexpr int getDistance (void) const noexcept { return this->distance; };
    inline City *getStartCity (void) { return this->cityStart; };
    inline City *getEndCity (void) { return this->cityEnd; };

private:
    QColor color {Qt::black};
    City *cityStart;
    City *cityEnd;
    int distance;

    void toggleColor (bool allBlack = false);
};