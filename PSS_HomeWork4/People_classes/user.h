#ifndef USER_H
#define USER_H

#include "people.h"
#include "Additional_classes/order.h"

class User : public People
{
protected:
    std::vector<Order> order_history;
public:
    User(const People& p, const std::vector<Order>&);

    void printOrderHistory() const;
    std::vector<Order> getOrderHistory() const;
};

#endif // USER_H
