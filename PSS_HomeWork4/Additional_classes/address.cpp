#include "address.h"

#include <QDebug>

Address::Address(const std::string& s)
    :std::string(s)
{}

void Address::setName(const std::string& name)
{
    shortName = name;
}

std::string Address::name()
{
    return shortName;
}

std::ostream& operator<<(std::ostream &out, const Address &A){
    if(A.shortName.size() > 0)
        out<<"( "<<A.shortName<<" ) ";
    out<<static_cast<std::string>(A);
    return out;
}
