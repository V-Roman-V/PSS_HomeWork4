#ifndef DRIVER_H
#define DRIVER_H

#include "user.h"
#include <vector>
#include "Enumerations/rating.h"
#include "Enumerations/cartype.h"
#include "Enumerations/status.h"
#include "Additional_classes/order.h"

class Driver : public User
{
public:
    Driver(const User& p, Rating rating);

    std::vector<Order> getOrderHistory() const;

    void seeACar(); // print info about Car;

    void updateStatus();

    Order takeOrder();

private:
    Rating rating;
    std::vector<Order> order_history;
    CarType car;
    std::vector<Order> pinned_addresses;
    Status status;
};
#endif // DRIVER_H
