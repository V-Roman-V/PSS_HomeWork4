#ifndef PASSENGER_H
#define PASSENGER_H

#include <vector>
#include "user.h"
#include "Enumerations/rating.h"
#include "Enumerations/paytype.h"
#include "Additional_classes/order.h"

class Passenger : public User
{
public:
    Passenger(const User&, const Rating&, const std::vector<Address>&);

    //WTF
    void askAboutCoordinates();//???

    Order makeOrder();

    std::string getFullInfo()const override;

    PayType getPayMethod() const;

private:
    Rating rating;
    // TODO способ оплаты
    std::vector<Address> pinned_addresses;
    PayType pay_method;
};

#endif // PASSENGER_H
