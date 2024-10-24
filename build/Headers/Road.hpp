#pragma once

#include "City.hpp"
#include <string>
#include <QPainter>
#include <QWidget>
#include <cmath>

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

        int dx = endX - startX;
        int dy = endY - startY;

        double dOriginal = std::sqrt(dx * dx + dy * dy);

        double deslocamento = 15.0 / dOriginal;

        int x1Novo = startX + deslocamento * dx;
        int y1Novo = startY + deslocamento * dy;
        int x2Novo = endX - deslocamento * dx;
        int y2Novo = endY - deslocamento * dy;

        painter.drawLine(x1Novo, y1Novo, x2Novo, y2Novo); 
        setFixedSize(900,900);
        move(15, 15);
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