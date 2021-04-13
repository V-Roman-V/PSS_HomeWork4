#include "driver.h"

Driver::Driver(const People &p, Rating rating)
    :People(p), rating(rating)
{}

std::vector<Order> Driver::getOrderHistory() const {
    return order_history;
}

