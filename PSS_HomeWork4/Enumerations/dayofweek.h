#ifndef DAYOFWEEK_H
#define DAYOFWEEK_H

#include <string>

class DayOfWeek{
    static const uint8_t countDays = 7;

    enum class DayName{
        Monday = 1,
        Tuesday,
        Wednesday, // 3
        Thursday,
        Friday,
        Saturday,
        Sunday     // 7
    } day;

    static std::string enumToStr(DayName name);
    static DayName intToEnum(int val);
public:
    explicit DayOfWeek(int d = 1);

    operator DayName() {return day;}
    int number() const;

    bool operator== (const DayOfWeek& d) const;
    bool operator!= (const DayOfWeek& d) const;
    bool operator<  (const DayOfWeek& d) const;
    bool operator>  (const DayOfWeek& d) const;
    bool operator<= (const DayOfWeek& d) const;
    bool operator>= (const DayOfWeek& d) const;

    DayOfWeek& operator=  (const DayOfWeek& d);
    DayOfWeek& operator=  (int d);
    DayOfWeek& operator+=  (int s);
    DayOfWeek& operator-=  (int s);
    DayOfWeek& operator++ ();
    DayOfWeek& operator-- ();
    DayOfWeek operator+ (int s) const;
    DayOfWeek operator-  (int s) const;

    friend std::ostream& operator<< (std::ostream &out, const DayOfWeek &D);
};

#endif // DAYOFWEEK_H
