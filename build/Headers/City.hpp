#pragma once

#include <QPainter>
#include <string>
#include <QWidget>

class City final : public QWidget {
    Q_OBJECT
public:
    City (std::string __cityName, int x, int y, QWidget *parent = nullptr);

    inline void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);

        const int radius = 15;
        
        painter.setBrush(Qt::black);
        painter.drawEllipse(QPoint(radius, radius), radius, radius);
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 9));

        QString text {QString::fromStdString(itsName).sliced(0, 3)};

        painter.drawText(5, 18, text);

        setFixedSize(900, 900);
        this->move(x, y);
    }

    inline std::string getName (void) const { return this->itsName; }
    inline constexpr int getX (void) const noexcept { return this->x; };
    inline constexpr int getY (void) const noexcept  { return this->y; }

private:
    std::string itsName;
    int x;
    int y;
};