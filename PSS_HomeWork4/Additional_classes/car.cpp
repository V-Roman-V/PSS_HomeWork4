#include "car.h"
#include <iostream>

void Car::setBottles(int n)
{
    free_bottle_of_water=n;
}

void Car::parkRightInFrontOfTheEntrance()
{
    //TODO
}

std::ostream& operator<<(std::ostream &out, const Car &C){
    out<<"Car{number: "<<C.number<<",";
    out<<"model: "         <<C.model<<",";
    out<<"type: "       <<C.type<<",";
    out<<"color: "        <<C.color<<",";
    out<<"coordinates: "        <<C.coordinates.x()<<";"<<C.coordinates.y()<<"}";
    return out;
}

void Car::print() const
{
    std::cout<<"Car number      : "<<number<<std::endl;
    std::cout<<"    model       : "<<model<<std::endl;
    std::cout<<"    type        : "<<type<<std::endl;
    std::cout<<"    color       : "<<color<<std::endl;
    std::cout<<"    coordinates : "<<coordinates.x()<<","<<coordinates.y()<<std::endl;
    if(type.number()>=2)
        std::cout<<"    bottles     : "<<free_bottle_of_water<<std::endl;
}
