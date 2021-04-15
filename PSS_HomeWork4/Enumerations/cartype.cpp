#include "cartype.h"

std::vector<std::string> CarType::getList()
{
    std::vector<std::string> list;
    list.push_back(enumToStr(CarTypeNames::Economy));
    list.push_back(enumToStr(CarTypeNames::Comfort));
    list.push_back(enumToStr(CarTypeNames::ComfortPlus));
    list.push_back(enumToStr(CarTypeNames::Business));
    return list;
}

std::string CarType::enumToStr(CarType::CarTypeNames name){
    switch(name){
        case CarTypeNames::Economy:     return "Economy";
        case CarTypeNames::Comfort:     return "Comfort";
        case CarTypeNames::ComfortPlus: return "ComfortPlus";
        case CarTypeNames::Business:    return "Business";
    }
}

CarType::CarTypeNames CarType::intToEnum(int val){
    switch(val){
        case 0: return CarTypeNames::Economy;
        case 1: return CarTypeNames::Comfort;
        case 2: return CarTypeNames::ComfortPlus;
        case 3: return CarTypeNames::Business;
    }
    return CarTypeNames::Economy;
}

std::ostream& operator<<(std::ostream &out, const CarType &C){
    return out<<CarType::enumToStr(C.car);
}

