#ifndef DATE_H
#define DATE_H

#include <sstream>
#include <ctime>
#include <string>
#include "Enumerations/dayofweek.h"
#include "Enumerations/month.h"

class Date
{
private:
    Date(uint16_t d, uint16_t m, uint16_t y, uint16_t dow);
    static Date getPivotDate();
    int toDays() const;

public:
    Date(){operator=(Date::getNowDate());}
    Date(uint16_t d, uint16_t m, uint16_t y):Date(d,m,y,0){}

    bool isCorrect() const;

    bool operator== (const Date& d){return dateDiff(d)==0;}
    bool operator!= (const Date& d){return !operator==(d);}
    bool operator<  (const Date& d){return dateDiff(d)<0;}
    bool operator>  (const Date& d){return dateDiff(d)>0;}
    bool operator<= (const Date& d){return dateDiff(d)<=0;}
    bool operator>= (const Date& d){return dateDiff(d)>=0;}

    Date& operator+= (int sh);
    Date& operator-= (int sh);
    Date& operator++ ();
    Date& operator-- ();
    Date operator+ (int sh) const;
    Date operator- (int sh) const;

    Date shiftDay(const int days) const;

    unsigned short getAgeDiff(const Date &d) const;

    int dateDiff(const Date& right) const;

    friend std::ostream &operator<< (std::ostream &out, const Date &D);

    static bool isLeapYear(uint16_t year);

    static Date getNowDate();

    Date beginWeek();
    Date endWeek();
private:
    uint16_t year;
    Month month;
    uint16_t day;
    DayOfWeek day_of_week;
};

#endif // DATE_H
