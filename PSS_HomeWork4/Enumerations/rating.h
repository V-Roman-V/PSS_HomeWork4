#ifndef RATING_H
#define RATING_H

#include <string>

class Rating
{
    enum class RatingName{
        Bad = 1,  // 1
        NotGood,
        Normal,
        Good,
        Excellent  // 5
    } rating;

    static std::string enumToStr(RatingName name);

    static RatingName intToEnum(int val);

public:
    explicit Rating(int r = 0): rating( intToEnum(r) ){}

    operator RatingName(){return rating;}

    int number() const {return static_cast<int>(rating);}

    friend std::ostream& operator<< (std::ostream &out, const Rating &R);
};
#endif // RATING_H
