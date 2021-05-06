#ifndef MONTH_H
#define MONTH_H

#include <string>

class Month{
    static const uint8_t countMonths = 12;

    enum class MonthName{
        January = 1,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December // 12
    } month;

    static std::string enumToStr(MonthName name);
    static MonthName intToEnum(int val);

public:
    Month(int m = 1);

    operator MonthName() {return month;}
    int number() const;

    Month& operator=  (const Month& m);
    Month& operator=  (int m);

    bool operator== (const Month& m) const;
    bool operator!= (const Month& m) const;
    bool operator<  (const Month& m) const;
    bool operator>  (const Month& m) const;
    bool operator<= (const Month& m) const;
    bool operator>= (const Month& m) const;

    Month& operator+= (int sh);
    Month& operator-= (int sh);
    Month& operator++ ();
    Month& operator-- ();
    Month operator+ (int s) const;
    Month operator- (int s) const;

    friend std::ostream& operator<< (std::ostream &out, const Month &M);

    int countDays(bool vis = false) const;
};

#endif // MONTH_H
