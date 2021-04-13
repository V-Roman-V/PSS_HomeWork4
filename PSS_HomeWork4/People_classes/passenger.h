#ifndef PASSENGER_H
#define PASSENGER_H

#include <vector>
#include "people.h"
#include "Enumerations/rating.h"
#include "Additional_classes/order.h"

class Passenger : public People
{
public:
    Passenger(const People& p, Rating rating);

    //WTF
    void askAboutCoordinates();//???

    Order makeOrder();

    std::vector<Order> getOrderHistory() const;

private:
    Rating rating;
    std::vector<Order> order_history;
    // TODO способ оплаты
    std::vector<Order> pinned_addresses;
};

#endif // PASSENGER_H
