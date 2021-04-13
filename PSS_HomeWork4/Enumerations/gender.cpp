#include "gender.h"

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

std::ostream& operator<<(std::ostream &out, const Gender &G){
    return out<<Gender::enumToStr(G.gender);
}

