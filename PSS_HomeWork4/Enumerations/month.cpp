#include "month.h"

std::string Month::enumToStr(Month::MonthName name){
    switch(name){
    case MonthName::January:return"January";
    case MonthName::February:return"February";
    case MonthName::March:return"March";
    case MonthName::April:return"April";
    case MonthName::May:return"May";
    case MonthName::June:return"June";
    case MonthName::July:return"July";
    case MonthName::August:return"August";
    case MonthName::September:return"September";
    case MonthName::October:return"October";
    case MonthName::November:return"November";
    case MonthName::December:return"December";
    }
}

Month::MonthName Month::intToEnum(int val){
    switch(val){
    case 1: return MonthName::January;
    case 2: return MonthName::February;
    case 3: return MonthName::March;
    case 4: return MonthName::April;
    case 5: return MonthName::May;
    case 6: return MonthName::June;
    case 7: return MonthName::July;
    case 8: return MonthName::August;
    case 9: return MonthName::September;
    case 10: return MonthName::October;
    case 11:return MonthName::November;
    case 12:return MonthName::December;
    }
    return MonthName::December;
}

Month::Month(int m): month( intToEnum(m) ){}

int Month::number() const {return static_cast<int>(month);}

Month &Month::operator=(int m) {month = intToEnum(m); return *this;}

bool Month::operator==(const Month &m) const{return number() == m.number();}

bool Month::operator!=(const Month &m) const{return number() != m.number();}

bool Month::operator<(const Month &m) const {return number() < m.number();}

bool Month::operator>(const Month &m) const {return number() > m.number();}

bool Month::operator<=(const Month &m) const {return number() <= m.number();}

bool Month::operator>=(const Month &m) const {return number() >= m.number();}

Month &Month::operator+=(int sh) {
    month = intToEnum( (static_cast<int>(month) - 1 + sh%countMonths + countMonths)%countMonths + 1);
    return *this;
}

Month &Month::operator-=(int sh) {return operator+=(-sh);}

Month &Month::operator++() {return operator+=(1);}

Month &Month::operator--() {return operator-=(1);}

Month Month::operator+(int s) const {Month curM(*this);return curM+=s;}

Month Month::operator-(int s) const{return operator+(-s);}

int Month::countDays(bool vis) const{
    switch(month){
    case MonthName::January:
    case MonthName::March:
    case MonthName::May:
    case MonthName::July:
    case MonthName::August:
    case MonthName::October:
    case MonthName::December: return 31;
    case MonthName::September:
    case MonthName::April:
    case MonthName::June:
    case MonthName::November: return 30;
    case MonthName::February: return 28 + vis;
    }
}

std::ostream& operator<<(std::ostream &out, const Month &M){
    return out<<Month::enumToStr(M.month);
}

Month &Month::operator=(const Month &m) {month = m.month; return *this;}
