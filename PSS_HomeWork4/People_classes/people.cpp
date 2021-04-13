#include "people.h"
#include <sstream>

People::People(const std::string &_name, const std::string& _surname, const Gender &_gender, const Date &_date_of_birth, const Passport &_passport, const std::string &_phone_number, const std::string &_nationality)
    :name(_name),surname(_surname), date_of_birth(_date_of_birth), passport(_passport), gender(_gender), nationality(_nationality), phone_number(_phone_number)
{}

std::string People::getCommonInfo()const
{
    std::stringstream info;
    info <<"\tname: "<<getName()<<std::endl;
    info <<"\tage: "<<getAge()<<std::endl;
    return info.str();
}

std::string People::getFullInfo()const
{
    std::stringstream info;
    info <<"\tname: "<<name<<" "<<surname<<std::endl;

    info <<"\tgender: "<<gender;
    info <<std::endl;
    info <<"\tage: "<<((date_of_birth.isCorrect())?std::to_string(getAge()):"-")<<std::endl;
    if(passport.isCorrect())
        info <<"\tpassport: "<<passport<<std::endl;
    if(phone_number.size() > 5)
        info <<"\tphone number: "<<phone_number<<std::endl;
    if(nationality.size() > 2)
        info <<"\tnationality: "<<nationality<<std::endl;
    return info.str();
}

std::string People::getName() const
{
    return name +" "+ surname;
}

unsigned short People::getAge() const
{
    return date_of_birth.getAgeDiff(Date::getNowDate());
}
