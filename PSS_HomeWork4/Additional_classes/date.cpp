#include "date.h"


Date::Date(uint16_t d, uint16_t m, uint16_t y, uint16_t dow):year(y), month(m), day(d){
    if(month.countDays(isLeapYear(year)) < day)
        day = month.countDays(isLeapYear(year));
    if(dow>0)
        day_of_week = dow;
    else
        day_of_week = (getPivotDate().day_of_week + dateDiff(getPivotDate()));
}

Date &Date::operator+=(int sh){
    shiftDay(sh);
    return *this;
}

Date &Date::operator-=(int sh){return operator+=(-sh);}

Date &Date::operator++(){return operator+=(1);}

Date &Date::operator--(){return operator-=(1);}

Date Date::operator+(int sh) const {
    Date curI(*this);
    return curI+=sh;
}

Date Date::operator-(int sh) const {return operator+(-sh);}

Date Date::shiftDay(const int days) const{
    int shift = days;
    Date nextDate(*this);
    while(shift > 0){
        int Mlim = nextDate.month.countDays(isLeapYear(nextDate.year));
        if(nextDate.day + shift > Mlim){
            shift = shift - Mlim + nextDate.day - 1;
            nextDate.day = 1;
            if(nextDate.month.number() != 12)
                nextDate.month = nextDate.month+1;
            else{
                nextDate.month = 1;
                nextDate.year+=1;
            }
        } else {
            nextDate.day +=shift;
            shift = 0;
        }
    }
    while(shift < 0){
        if(nextDate.day + shift < 1){
            shift += nextDate.day;
            if(nextDate.month.number() != 1)
                nextDate.month = nextDate.month-1;
            else{
                nextDate.month = 12;
                nextDate.year-=1;
            }
            nextDate.day = nextDate.month.countDays(isLeapYear(nextDate.year));
        } else {
            nextDate.day +=shift;
            shift = 0;
        }
    }

    nextDate.day_of_week = nextDate.day_of_week + (dateDiff(nextDate));

    return nextDate;
}

unsigned short Date::getAgeDiff(const Date &r) const
{
    short diff = year - r.year - ((r.month > month)?1:((r.month == month)&&(r.day > day)));
    if(diff<0)
        diff = r.year - year - ((month > r.month)?1:((month == r.month)&&(day > r.day)));
    return diff;
}

int Date::toDays() const { // from 1900 years;
    int days = 0;
    int countLeap = 0;
    for(int i = 1900; i<year; i+=4)
        countLeap += isLeapYear(i);
    days += countLeap*366 + (year - 1900 - countLeap)*365;

    bool leap = isLeapYear(year);
    for(int i = 1; i<month.number(); i++)
        days += Month(i).countDays(leap);

    days += day;
    return days;
}

Date::Date(const QDate &d)
    :Date(d.day(),d.month(),d.year())
{}

bool Date::isCorrect() const
{
    return toDays()!=1;
}

int Date::dateDiff(const Date &right) const{
    int diff = toDays() - right.toDays();
    return diff;
}

std::ostream& operator<<(std::ostream &out, const Date &D){
    return out<<D.day_of_week<<" "<<D.day<<" "<<D.month<<" "<<D.year;
}

bool Date::isLeapYear(uint16_t year){
    return year%4 == 0 && (year%100 != 0 || year%400 == 0);
}

Date Date::getPivotDate(){
    return Date(1,1,1900,1); // 1 January - Monday
}

Date Date::getNowDate(){
    std::time_t t = std::time(nullptr);   // get time now
    std::tm* now = std::localtime(&t);
    Date now_date(now->tm_mday,now->tm_mon+1,(now->tm_year + 1900));
    return now_date;
}

Date Date::beginWeek() {
    Date today(*this);
    return today -= (today.day_of_week.number()-1);
}

Date Date::endWeek() {
    return beginWeek()+=7;
}
