#include "passenger.h"

Passenger::Passenger(const User &u, const Rating &rating, const std::vector<Address> &addresses)
    :User(u), rating(rating), pinned_addresses(addresses)
{std::cout<<"ok";}

std::string Passenger::getFullInfo() const
{
    std::stringstream info;
    info<<User::getFullInfo();
    if(pinned_addresses.size()>0){
        info<<"\tPinned addresses:"<<std::endl;
        for(const Address& addr:pinned_addresses)
            info<<"\t\t"<<addr<<std::endl;
    }
    return info.str();
}

