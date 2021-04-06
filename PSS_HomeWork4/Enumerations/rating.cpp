#include "rating.h"

std::string Rating::enumToStr(Rating::RatingName name){
    switch(name){
        case RatingName::Bad:       return "Bad";
        case RatingName::NotGood:   return "NotGood";
        case RatingName::Normal:    return "Normal";
        case RatingName::Good:      return "Good";
        case RatingName::Excellent: return "Excellent";
    }
}

Rating::RatingName Rating::intToEnum(int val){
    switch(val){
        case 1: return RatingName::Bad;
        case 2: return RatingName::NotGood;
        case 3: return RatingName::Normal;
        case 4: return RatingName::Good;
        case 5: return RatingName::Excellent;
    }
    return RatingName::Excellent;
}

std::ostream& operator<<(std::ostream &out, const Rating &R){
    return out<<Rating::enumToStr(R.rating);
}

