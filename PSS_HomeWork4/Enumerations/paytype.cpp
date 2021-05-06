#include "paytype.h"

std::string PayType::enumToStr(PayType::PayName name){
    switch(name){
        case PayName::Cash:    return "Cash";
        case PayName::Noncash: return "Noncash";
    }
}

PayType::PayName PayType::intToEnum(int val){
    switch(val){
        case 0: return PayName::Cash;
        case 1: return PayName::Noncash;
    }
    return PayName::Noncash;
}

std::ostream& operator<<(std::ostream &out, const PayType &P){
    return out<<PayType::enumToStr(P.type);
}

