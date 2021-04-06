#include "passenger.h"

Passenger::Passenger()
{

}

std::vector<Order> Passenger::getOrderHistory() const {
    return order_history;
}
