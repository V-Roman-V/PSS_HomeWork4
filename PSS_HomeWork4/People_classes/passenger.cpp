#include "passenger.h"

Passenger::Passenger(const User &u, const std::vector<Address> &addresses)
    :User(u), pinned_addresses(addresses)
{std::cout<<"ok";}

void Passenger::askAboutCoordinates()
{
    std::cout<<"You missed your train. It was getting late. So you decided to take a cab home. A red Renault was given to you. You sat in the back, looked out the window, and ate an apple. Suddenly, in a deserted place, the driver see a girl in a wedding dress (why not give her a lift). The cab driver stops and the girl sits down next to him without uttering a word. You can't see her face under the veil. Let's go. Out of the corner of your eye you watch the bride. The car smelled damp. \"There are swamps near here,\" the driver said. At that moment a minibus came around the corner. Both cars braked. An apple fell out of her hands and rolled under the seat of her traveling companion. You wanted to bend down to get it, but suddenly the bride hissed and quickly picked up her feet, you suddenly notice that she has hooves instead of feet. You immediately jump out of the car and run to the shuttle bus, waving your hands to keep it from leaving. Behind you, rustling her dress, the bride runs. The door opens and you dive in and fall on the last seat. The driver's voice: \"Sorry, there are no vacant seats, the traffic police are ahead, I do not take standing positions\". The door slams. The bus starts, picking up speed. Shivering with all your body you look out the back window: next to the shuttle runs the bride. The veil is developing and her pale face, twisted with anger, blue-tinged lips can be seen. You freeze in horror, and cannot make a sound, only trembling. \"End of the line,\" the driver announced. Stepping out of the shuttle with the other passengers, you ran with the crowd to the subway. Then you called your friend Olga to meet you and take you to sleep over. An hour later you are already sitting in the kitchen, drinking hot tea and coming to your senses. You turn on the TV. The crime news showed a live broadcast from the scene of the accident: a car was found in the middle of the road outside the city, and the dismembered body of the driver was beside it. The camera showed a red car in the dark... ";
    std::cout<<std::endl<<"P.S. This is a machine translation of a random story, I just put it in so that the function is not empty."<<std::endl;
}

std::string Passenger::getFullInfo() const
{
    std::stringstream info;
    info<<User::getFullInfo();
    info<<"\tPayment method: "<<pay_method<<std::endl;
    if(pinned_addresses.size()>0){
        info<<"\tPinned addresses:"<<std::endl;
        int i=0;
        for(const Address& addr:pinned_addresses)
            info<<"\t\t"<<i++<<") "<<addr<<std::endl;
    }
    return info.str();
}

PayType Passenger::getPayMethod() const
{
    return pay_method;
}

void Passenger::setPayMethod(const PayType &value)
{
    pay_method = value;
}

void Passenger::addPinAddress(const Address &addr)
{
    pinned_addresses.push_back(addr);
}

std::vector<Address> Passenger::getPinnedAddresses() const
{
    return pinned_addresses;
}

