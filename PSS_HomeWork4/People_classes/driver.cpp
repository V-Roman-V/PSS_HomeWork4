#include "driver.h"

Driver::Driver(const User& u, const Car& car)
    :User(u), car(car)
{}

std::vector<Order> Driver::getOrderHistory() const {
    return order_history;
}

std::string Driver::getFullInfo() const
{
    // TODO implement
    std::stringstream info;
    info<<User::getFullInfo();
    return info.str();
}

void Driver::updateStatus(Status s)
{
    status = s;
}

Order Driver::takeOrder()
{
    //TODO

}

Car Driver::getCar() const
{
    return car;
}

