#include "passenger.h"

Passenger::Passenger(const People &p, Rating rating)
    :People(p), rating(rating)
{}

std::vector<Order> Passenger::getOrderHistory() const {
    return order_history;
}
