#ifndef DRIVER_H
#define DRIVER_H

#include "user.h"
#include <vector>
#include "Enumerations/status.h"
#include "Additional_classes/order.h"
#include "Additional_classes/car.h"

class Driver : public User
{
public:
    Driver(const User& u, const Car& car);

    std::vector<Order> getOrderHistory() const;

    std::string getFullInfo()const override;

    void updateStatus(Status s);

    Order takeOrder();

    Car getCar() const;

    Status getStatus() const;

private:
    std::vector<Order> order_history;
    Car car;
    Status status;
};
#endif // DRIVER_H
