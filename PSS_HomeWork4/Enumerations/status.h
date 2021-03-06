#ifndef STATUS_H
#define STATUS_H

#include <string>

class Status
{
    enum class StatusName{
        Free,
        Busy
    } status;

    static std::string enumToStr(StatusName name);

    static StatusName intToEnum(int val);

public:
    explicit Status(int s = 0): status( intToEnum(s) ){}

    operator StatusName()const{return status;}
    operator std::string()const{return enumToStr(status);}

    int number() const {return static_cast<int>(status);}

    friend std::ostream& operator<< (std::ostream &out, const Status &R);
};

#endif // STATUS_H
