#ifndef CARTYPE_H
#define CARTYPE_H

#include <string>

class CarType{
    static const uint8_t countCars = 4;

    enum class CarTypeNames{
        Economy,  // 0
        Comfort,
        ComfortPlus,
        Business  // 3
    } car;

    static std::string enumToStr(CarTypeNames name);

    static CarTypeNames intToEnum(int val);

public:
    explicit CarType(int d = 0): car( intToEnum(d) ){}

    operator CarTypeNames(){return car;}

    int number() const {return static_cast<int>(car);}

    friend std::ostream& operator<< (std::ostream &out, const CarType &C);
};

#endif // CARTYPE_H
