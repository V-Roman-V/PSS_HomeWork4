#ifndef USER_H
#define USER_H

#include "people.h"
#include "Additional_classes/order.h"
#include "Enumerations/rating.h"

class User : public People
{
protected:
    std::vector<Order> order_history;
    Order current_order;
    bool _hasActiveOrder=false;
    Rating rating;
public:
    User(const People& p, const std::vector<Order>&, const Rating&);

    std::string getFullInfo()const override;

    void printOrderHistory() const;
    std::vector<Order> getOrderHistory() const;
    void setCurrentOrder(const Order&);
    void deleteCurrentOrder();
    void closeCurrentOrder();
    bool hasActiveOrder() const;
    Order getCurrentOrder() const;
};

#endif // USER_H
