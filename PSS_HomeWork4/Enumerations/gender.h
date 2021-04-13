#ifndef GENDER_H
#define GENDER_H

#include <string>

class Gender
{
    enum class GenderName{
        unknown = 0,
        male,
        female
    } gender;

    static std::string enumToStr(GenderName name);

    static GenderName intToEnum(int val);

    int number() const {return static_cast<int>(gender);}

public:
    explicit Gender(int g = 0): gender( intToEnum(g) ){}

    operator GenderName(){return gender;}

    friend std::ostream& operator<< (std::ostream &out, const Gender &G);
};

#endif // GENDER_H
