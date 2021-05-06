#include "passport.h"

Passport::Passport(unsigned int _series, unsigned int _number)
    :number(_number), series(_series)
{}

void Passport::setPassport(unsigned int _series, unsigned int _number)
{
    number=_number;
    series=_series;
}

unsigned int Passport::getNumber() const
{
    return number;
}

unsigned int Passport::getSeries() const
{
    return series;
}

bool Passport::isCorrect()const
{
    return series!=0;
}

std::ostream& operator<<(std::ostream& os, const Passport& p){
    return os<<p.getSeries()<<" "<<p.getNumber();
}
