#ifndef GENDER_H
#define GENDER_H

#include <string>
#include <vector>

class Gender
{
    enum class GenderName{
        unknown = 0,
        male,
        female
    } gender;

    static std::vector<Gender> getList();

    static std::string enumToStr(GenderName name);

    static GenderName intToEnum(int val);

    int number() const {return static_cast<int>(gender);}

    Gender(GenderName g): gender(g){}

public:
    explicit Gender(int g = 0): gender( intToEnum(g) ){}

    operator GenderName() const {return gender;}

    static Gender fromString(const std::string&);

    friend std::ostream& operator<< (std::ostream &out, const Gender &G);
};

#endif // GENDER_H
