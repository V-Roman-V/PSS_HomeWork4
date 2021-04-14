#include "user.h"

User::User(const People &p, const std::vector<Order>& orders)
    :People(p), order_history(orders)
{std::cout<<"oku";}

std::vector<Order> User::getOrderHistory() const {
    return order_history;
}


void User::printOrderHistory() const
{
    for(const auto& order:order_history){
        order.print();
        std::cout<<std::endl;
    }
}
