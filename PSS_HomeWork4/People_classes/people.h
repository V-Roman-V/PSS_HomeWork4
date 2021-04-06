#ifndef PEOPLE_H
#define PEOPLE_H
#include <string>
#include "Additional_classes/date.h"
#include "Additional_classes/passport.h"
#include <ctime>

class People
{
public:
    enum class Gender{unknown, male, female};
    People() = default;

    People(const std::string& _name,
           const std::string& _surname,
           const Gender& _gender = Gender::unknown,
           const Date& _date_of_birth = Date(),
           const Passport& _passport = Passport(),
           const std::string& _phone_number = "",
           const std::string& _nationality = ""
          );
    virtual ~People() = default;

    virtual std::string getCommonInfo()const;
    virtual std::string getFullInfo()const;

    std::string getName() const;
    unsigned short getAge() const;
private:
    std::string name;
    std::string surname;
    Date date_of_birth;
    Passport passport;
    Gender gender;
    std::string nationality;
    std::string phone_number;
};

#endif // PEOPLE_H
