#include "order.h"

std::ostream& operator<<(std::ostream &out, const Order &O){
    out<<"Order{number: "<<O.number<<",";
    out<<"car: "         <<O.car<<",";
    out<<"price: "       <<O.price<<",";
    out<<"time: "        <<O.time.toString().toStdString()<<",";
    out<<"date: "        <<O.date<<"}";
    return out;
}

void Order::print() const
{
    std::cout<<"Order number: "<<number<<std::endl;
    std::cout<<"      from  : "<<from<<std::endl;
    std::cout<<"      to    : "<<to<<std::endl;
    std::cout<<"      car   : "<<car<<std::endl;
    std::cout<<"      price : "<<price<<std::endl;
    std::cout<<"      time  : "<<time.toString().toStdString()<<std::endl;
    std::cout<<"      date  : "<<date<<std::endl;
}
