#ifndef ORDER_H
#define ORDER_H

#include <QTime>
#include <iostream>
#include "Additional_classes/address.h"
#include "Additional_classes/date.h"
#include "Enumerations/cartype.h"

struct Order
{
    int number;
    Address from;
    Address to;
    CarType car;
    double  price;
    QTime   time;
    Date   date;

    void print() const;
    friend std::ostream &operator<< (std::ostream &out, const Order &O);
};

#endif // ORDER_H
