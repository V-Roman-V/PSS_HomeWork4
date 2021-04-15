#include "user.h"

bool User::hasActiveOrder() const
{
    return _hasActiveOrder;
}

Order User::getCurrentOrder() const
{
    return current_order;
}

User::User(const People &p, const std::vector<Order>& orders)
    :People(p), order_history(orders)
{std::cout<<"oku";}

std::vector<Order> User::getOrderHistory() const {
    return order_history;
}

void User::setCurrentOrder(const Order &order)
{
    current_order=order;
    _hasActiveOrder = true;
}

void User::deleteCurrentOrder()
{
    _hasActiveOrder = false;
}

void User::closeCurrentOrder()
{
    if(!_hasActiveOrder)return;
    order_history.push_back(current_order);
    _hasActiveOrder=false;
}


void User::printOrderHistory() const
{
    for(const auto& order:order_history){
        order.print();
        std::cout<<std::endl;
    }
}
