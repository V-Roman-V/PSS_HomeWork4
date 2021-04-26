#ifndef PERSONTYPE_H
#define PERSONTYPE_H

#include <string>
#include <vector>

class PersonType
{
    static const uint8_t countTypes = 3;
    enum class PersonName{
        Passenger = 0,  // 1
        Driver,
        Admin
    } person;

    static std::string enumToStr(PersonName name);

    static PersonName intToEnum(int val);

public:
    static std::vector<std::string> getList();

    explicit PersonType(int p = 0): person( intToEnum(p) ){}

    operator PersonName() const {return person;}
    operator std::string() const {return enumToStr(person);}

    int number() const {return static_cast<int>(person);}

    friend std::ostream& operator<< (std::ostream &out, const PersonType &P);
};
#endif // PERSONTYPE_H
