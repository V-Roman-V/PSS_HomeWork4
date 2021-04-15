#ifndef CARTYPE_H
#define CARTYPE_H

#include <string>
#include <vector>

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

    CarType(CarTypeNames n): car(n){}

public:
    explicit CarType(int d = 0): car( intToEnum(d) ){}

    static std::vector<std::string> getList();

    operator CarTypeNames(){return car;}

    int number() const {return static_cast<int>(car);}

    friend std::ostream& operator<< (std::ostream &out, const CarType &C);
};

#endif // CARTYPE_H
