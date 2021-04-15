#ifndef COMMONINTERFACE_H
#define COMMONINTERFACE_H

#include <iostream>
#include <string>
#include <vector>
#include "People_classes/user.h"
#include "People_classes/driver.h"
#include "People_classes/passenger.h"
#include "Interfaces/databaseinterface.h"
#include "Enumerations/persontype.h"
#include "Enumerations/cartype.h"

class CommonInterface : public DataBaseInterface
{
public:
    CommonInterface();
    ~CommonInterface();
    virtual bool start();

protected:
    bool Hello();
    bool Login();
    bool Menu();

    void SeeHistory();

    bool DrivMenu();
    void D_SeeCar();
    void D_TakeOrder();
    void D_SeeOrder();

    // TODO put together
    bool PassMenu();
    void P_ChangePay();
    void P_AddPinAddr();
    void P_MakeOrder();
    Address P_ChooseAddr(bool from);
    CarType P_ChooseCar();
    void P_CreateOrder(const Order& order);
    void P_SeeOrder();


    static inline void print(const std::string& s){std::cout<<s<<std::endl;}
    static inline void getInput(std::string& input){std::cout<<'>';std::cin>>input;}
    static inline void waitENTER();
    static inline bool isNumber(const std::string& num){return num.size()>0 && (num.find_first_not_of( "0123456789" ) == std::string::npos);}
    static inline void clear(){system("cls");}

    PersonType type;
    User* person;

    template<class T>
    static std::string getListOptions(const std::vector<T>& list);

    template<class T>
    static int calculateInput(const std::string& input, const std::vector<T>& list);


};

#endif // COMMONINTERFACE_H
