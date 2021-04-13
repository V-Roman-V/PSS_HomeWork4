#ifndef COMMONINTERFACE_H
#define COMMONINTERFACE_H

#include <iostream>
#include <string>
#include <vector>
#include "People_classes/people.h"
#include "People_classes/driver.h"
#include "People_classes/passenger.h"
#include "Interfaces/databaseinterface.h"
#include "Enumerations/persontype.h"

class CommonInterface : public DataBaseInterface
{
public:
    CommonInterface();

    bool Hello();
    bool Login();

protected:
    static inline void print(const std::string& s){std::cout<<s<<std::endl;}
    static inline void getInput(std::string& input){std::cout<<'>';std::cin>>input;}
    static inline void waitENTER();
    static inline bool isNumber(const std::string& num){return (num.find_first_not_of( "0123456789" ) == std::string::npos);}
    static inline void clear(){system("cls");}

    PersonType type;
    People* person;

    template<class T>
    static std::string getListOptions(const std::vector<T>& list);

    template<class T>
    static int calculateInput(const std::string& input, const std::vector<T>& list);


};

#endif // COMMONINTERFACE_H
