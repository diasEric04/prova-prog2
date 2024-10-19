#pragma once

#include "City.hpp"
#include <string>
#include <QPainter>
#include <QWidget>

class Road final : public QWidget {
    Q_OBJECT
public: 
    Road (City *__cityStart, City *__cityEnd, int __kmDistance, QWidget * parent = nullptr);

    inline void paintEvent (QPaintEvent *event) override {
        QPainter painter(this);
        QPen pen (Qt::black);
        pen.setWidth(3);
        painter.setPen(pen);
        painter.setBrush(Qt::black);
        painter.drawLine(startX, startY, endX, endY);
        setFixedSize(900,900);
        move(10, 10);
    }

    inline constexpr int getStartX (void) const noexcept { return this->startX; }
    inline constexpr int getStartY (void) const noexcept { return this->startX; }
    inline constexpr int getEndX (void) const noexcept { return this->endX; }
    inline constexpr int getEndY (void) const noexcept { return this->endY; }

private:
    int startX;
    int startY;
    int endX;
    int endY;
    int distance;
};