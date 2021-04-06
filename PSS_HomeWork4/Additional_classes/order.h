#ifndef ORDER_H
#define ORDER_H

#include <QTime>
#include "Additional_classes/address.h"
#include "Enumerations/cartype.h"

class Order
{
public:
    Order();

private:
    Address from;
    Address to;
    CarType car;
    double  price;
    QTime   time;
    QDate   date;
};

#endif // ORDER_H
