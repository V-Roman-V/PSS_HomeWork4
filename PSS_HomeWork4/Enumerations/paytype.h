#ifndef PAYTYPE_H
#define PAYTYPE_H

#include <string>

class PayType
{
    enum class PayName{
        Cash = 1,  // 1
        Noncash
    } type;
    static std::string enumToStr(PayName name);

    static PayName intToEnum(int val);

public:
    explicit PayType(int t = 0): type( intToEnum(t) ){}

    operator PayName(){return type;}

    int number() const {return static_cast<int>(type);}

    friend std::ostream& operator<< (std::ostream &out, const PayType &P);
};

#endif // PAYTYPE_H
