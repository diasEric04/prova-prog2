#pragma once

#include <QPainter>
#include <string>
#include <QWidget>
#include <QMouseEvent>
#include <vector>

class City final : public QWidget {
    Q_OBJECT
    friend class Dialog;
public:
    City (std::string __cityName, int x, int y, QWidget *parent = nullptr);

    inline void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        painter.setBrush(bgColor);
        painter.drawEllipse(QRect(0, 0, size, size));

        painter.setPen(textColor);
        painter.setFont(QFont("Arial", 9));

        QString text {QString::fromStdString(itsName).sliced(0, 3)};
        
        painter.drawText(5, 20, text);
    }

    void mousePressEvent (QMouseEvent *event) override {
        emit cityClick (this);
        toggleColors();
    }   

    bool operator== (City *__city);
    void addNeighbor (City *__city);


    inline const std::string getName (void) const { return this->itsName; };
    inline constexpr int getX (void) const noexcept { return this->x; };
    inline constexpr int getY (void) const noexcept  { return this->y; };
    inline const std::vector<City*> getNeighbors (void) const noexcept { return this->neighbors; };

signals:
    void cityClick (City *__city);

private:
    QColor bgColor {Qt::black};
    QColor textColor {Qt::white};
    std::string itsName;
    int x;
    int y;
    const int size = 30;
    std::vector<City *> neighbors;

    void toggleColors (bool fTurnYellow = false);
};