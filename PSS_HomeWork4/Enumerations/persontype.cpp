#include "persontype.h"

std::string PersonType::enumToStr(PersonType::PersonName name){
    switch(name){
        case PersonName::Passenger: return "Passenger";
        case PersonName::Driver:    return "Driver";
    }
}

PersonType::PersonName PersonType::intToEnum(int val){
    switch(val){
        case 0: return PersonName::Passenger;
        case 1: return PersonName::Driver;
    }
    return PersonName::Passenger;
}

std::vector<std::string> PersonType::getList()
{
    std::vector<std::string> list;
    for( int i =0; i < countTypes;i++)
        list.push_back(PersonType(i));
    return list;
}

std::ostream& operator<<(std::ostream &out, const PersonType &P){
    return out<<PersonType::enumToStr(P.person);
}

