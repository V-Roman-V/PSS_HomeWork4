#include "driver.h"

Driver::Driver(const User &u, Rating rating)
    :User(u), rating(rating)
{}

std::vector<Order> Driver::getOrderHistory() const {
    return order_history;
}

