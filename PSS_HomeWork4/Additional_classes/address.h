#ifndef ADDRESS_H
#define ADDRESS_H

#include<string>
#include <ostream>

class Address: public std::string
{
    std::string shortName;
public:
    Address(const std::string& s = "");
    void setName(const std::string&);
    std::string name();

    void print() const;
    friend std::ostream &operator<< (std::ostream &out, const Address &A);
};

#endif // ADDRESS_H
