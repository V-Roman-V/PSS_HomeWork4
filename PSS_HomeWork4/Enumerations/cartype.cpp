#include "cartype.h"

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

