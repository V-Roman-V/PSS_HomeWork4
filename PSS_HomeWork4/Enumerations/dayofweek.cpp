#include "dayofweek.h"

std::string DayOfWeek::enumToStr(DayOfWeek::DayName name){
    switch(name){
    case DayName::Monday:return"Monday";
    case DayName::Tuesday:return"Tuesday";
    case DayName::Wednesday:return"Wednesday";
    case DayName::Thursday:return"Thursday";
    case DayName::Friday:return"Friday";
    case DayName::Saturday:return"Saturday";
    case DayName::Sunday:return"Sunday";
    }
}

DayOfWeek::DayName DayOfWeek::intToEnum(int val){
    switch(val){
    case 1: return DayName::Monday;
    case 2: return DayName::Tuesday;
    case 3: return DayName::Wednesday;
    case 4: return DayName::Thursday;
    case 5: return DayName::Friday;
    case 6: return DayName::Saturday;
    case 7: return DayName::Sunday;
    }
    return DayName::Saturday;
}

DayOfWeek::DayOfWeek(int d): day( intToEnum(d) ){}

int DayOfWeek::number() const {return static_cast<int>(day);}

bool DayOfWeek::operator==(const DayOfWeek &d) const {return  number() == d.number();}

bool DayOfWeek::operator!=(const DayOfWeek &d) const {return  number() != d.number();}

bool DayOfWeek::operator<(const DayOfWeek &d) const {return number() <  d.number();}

bool DayOfWeek::operator>(const DayOfWeek &d) const {return number() >  d.number();}

bool DayOfWeek::operator<=(const DayOfWeek &d) const {return number() <= d.number();}

bool DayOfWeek::operator>=(const DayOfWeek &d) const {return number() >= d.number();}

DayOfWeek &DayOfWeek::operator=(int d) {day = intToEnum(d); return *this;}

DayOfWeek &DayOfWeek::operator+=(int s) {
    day = intToEnum( (static_cast<int>(day) - 1 + s%countDays + countDays)%countDays + 1);
    return *this;
}

DayOfWeek &DayOfWeek::operator-=(int s) {return operator +=(-s);}

DayOfWeek &DayOfWeek::operator++() {return operator +=(1);}

DayOfWeek &DayOfWeek::operator--() {return operator -=(1);}

DayOfWeek DayOfWeek::operator+(int s) const {DayOfWeek curD(*this);return curD+=s;}

DayOfWeek DayOfWeek::operator-(int s) const {return operator+(-s);}

std::ostream& operator<<(std::ostream &out, const DayOfWeek &D){
    return out<<DayOfWeek::enumToStr(D.day);
}

DayOfWeek &DayOfWeek::operator=(const DayOfWeek &d) {day = d.day; return *this;}
