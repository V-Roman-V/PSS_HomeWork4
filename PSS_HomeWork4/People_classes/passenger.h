#ifndef PASSENGER_H
#define PASSENGER_H

#include <vector>
#include "user.h"
#include "Enumerations/paytype.h"
#include "Additional_classes/order.h"

class Passenger : public User
{
public:
    Passenger(const User&, const std::vector<Address>&);

    void askAboutCoordinates();//???

    Order makeOrder();

    std::string getFullInfo()const override;

    PayType getPayMethod() const;

    void setPayMethod(const PayType &value);

    void addPinAddress(const Address& addr);

    std::vector<Address> getPinnedAddresses() const;

private:
    std::vector<Address> pinned_addresses;
    PayType pay_method;
};

#endif // PASSENGER_H
