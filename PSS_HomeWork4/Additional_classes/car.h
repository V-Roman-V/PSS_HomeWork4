#ifndef CAR_H
#define CAR_H

#include "Enumerations/cartype.h"
#include <QPoint>
#include <QColor>
#include <ostream>

struct Car
{
    std::string model;
    CarType type;
    QPointF coordinates;
    std::string color;
    std::string number;
    void setBottles(int n);
    void parkRightInFrontOfTheEntrance(); //WTF

    void print() const;
    friend std::ostream &operator<< (std::ostream &out, const Car &C);

private:
    int free_bottle_of_water;
};

#endif // CAR_H
