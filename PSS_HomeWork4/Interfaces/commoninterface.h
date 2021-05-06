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
private:
    struct Gateway{
        virtual ~Gateway(){if(person)delete person;};
        virtual bool Menu()=0;
        void SeeHistory();
        User* person;
        CommonInterface* interface;
    protected:
        Gateway(CommonInterface* i):person(nullptr),interface(i){}
    };
public:
    CommonInterface();
    ~CommonInterface();
    virtual bool start();

protected:
    PersonType type;
    Gateway* gateway;

    bool Hello();
    bool Login();

    class DriverGateway : public Gateway{
    public:
        bool Menu() override;
        DriverGateway(CommonInterface* i):Gateway(i){};
    protected:
        void SeeCar();
        void TakeOrder();
        void SeeOrder();
        void setStatus();
    };

    class PassengerGateway : public Gateway{
    public:
        bool Menu() override;
        PassengerGateway(CommonInterface* i):Gateway(i){};
    protected:
        void ChangePay();
        void AddPinAddr();
        void MakeOrder();
        Address ChooseAddr(bool from);
        CarType ChooseCar();
        void CreateOrder(const Order& order);
        void SeeOrder();
    };

    // additional function
    static inline void print(const std::string& s){std::cout<<s<<std::endl;}
    static inline void getInput(std::string& input){std::cout<<'>';std::cin>>input;}
    static inline void waitENTER();
    static inline bool isNumber(const std::string& num){return num.size()>0 && (num.find_first_not_of( "0123456789" ) == std::string::npos);}
    static inline void clear(){system("cls");}

    template<class T>
    static std::string getListOptions(const std::vector<T>& list);

    template<class T>
    static int calculateInput(const std::string& input, const std::vector<T>& list);
};

#endif // COMMONINTERFACE_H
