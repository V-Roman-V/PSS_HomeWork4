#include "user.h"

bool User::hasActiveOrder() const
{
    return _hasActiveOrder;
}

Order User::getCurrentOrder() const
{
    return current_order;
}

User::User(const People &p, const std::vector<Order>& orders, const Rating&rating)
    :People(p), order_history(orders), rating(rating)
{std::cout<<"oku";}

std::string User::getFullInfo() const
{
    std::stringstream info;
    info<<People::getFullInfo();
    info<<"\tRating: "<<rating<<std::endl;
    return info.str();
}


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
