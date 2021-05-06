#include "driver.h"

Driver::Driver(const User& u, const Car& car)
    :User(u), car(car)
{}

std::vector<Order> Driver::getOrderHistory() const {
    return order_history;
}

std::string Driver::getFullInfo() const
{
    std::stringstream info;
    info<<User::getFullInfo();
    info<<"\tStatus:"<<static_cast<std::string>(status)<<std::endl;

    return info.str();
}

void Driver::updateStatus(Status s)
{
    status = s;
}

Car Driver::getCar() const
{
    return car;
}

Status Driver::getStatus() const
{
    return status;
}

