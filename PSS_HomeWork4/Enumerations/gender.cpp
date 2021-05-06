#include "gender.h"

std::vector<Gender> Gender::getList()
{
    std::vector<Gender> list;
    list.push_back(GenderName::unknown);
    list.push_back(GenderName::male);
    list.push_back(GenderName::female);
    return list;
}

std::string Gender::enumToStr(Gender::GenderName name){
    switch(name){
        case GenderName::unknown: return "unknown";
        case GenderName::male:    return "male";
        case GenderName::female:  return "female";
    }
}

Gender::GenderName Gender::intToEnum(int val){
    switch(val){
        case 0: return GenderName::unknown;
        case 1: return GenderName::male;
        case 2: return GenderName::female;
    }
    return GenderName::unknown;
}

Gender Gender::fromString(const std::string & s)
{
    for(const auto& gen : getList())
        if(enumToStr(gen) == s)
            return gen;
    return Gender(0);
}

std::ostream& operator<<(std::ostream &out, const Gender &G){
    return out<<Gender::enumToStr(G.gender);
}

