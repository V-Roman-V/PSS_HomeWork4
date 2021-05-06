#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include <string>
#include <algorithm>
#include <QCoreApplication>

#include "xlsxdocument.h"
#include "People_classes/people.h"
#include "People_classes/user.h"
#include "People_classes/passenger.h"
#include "People_classes/driver.h"
#include "People_classes/admin.h"
#include "Enumerations/persontype.h"


class DataBaseInterface
{
    enum ACCOUNTS_COLUMNS{
        NAME = 1,
        SURNAME,
        GENDER,
        DATEOFBIRTH,
        PASSSERIES,
        PASSNUMBER,
        PHONE,
        RATING,
        BLOCKED
    };
    enum ORDERS_COLUMNS{
        ORDERNUMBER = 1,
        ADDRESSFROM,
        ADDRESSTO,
        CARTYPE,
        PRICE,
        TIME,
        DATE,
        A_Pass,
        A_Status,
        A_LASTORDER
    };
    enum PASSENGER_COLUMNS{
        ORDERS = 1,
        PINNEDADDR,
        ADDRNAME
    };
    enum DRIVER_COLUMNS{
        ORDERS_D = 1,
        CARMODEL_D,
        CARTYPE_D,
        CARNUBER_D,
        CARCOLOR_D,
        CARVERIFIED_D
    };

    QXlsx::Document accounts;

    void fillDatabase();

    int findPerson(const std::string& phone)const;
    People getPerson(int p) const;
protected:
    std::pair<PersonType,int> getInfo(const std::string& phone);
    void blockPerson(PersonType, int row, bool block);
    void verifyCar(const std::string& phone, int row, bool verified);

    DataBaseInterface();

    int getNextOrderNumber();

    int findPassenger(const std::string& phone);
    Passenger getPassenger(int p);

    int findDriver(const std::string& phone);
    Driver getDriver(int p);

    int findAdmin(const std::string& phone);
    Admin getAdmin(int p);

    void savePinAddress(const std::string& phone, const Address& address);

    void closeActiveOrder(const Order& order, const std::string& Dphone);
    void takeActiveOrder(const Order& order);
    void saveActiveOrder(const Order& order,const std::string phone);
    void deleteActiveOrder(const Order& order);

    std::pair<bool,Status> getOrderStatus(int number);
    std::string getActiveOrderPhone(int number);

    std::vector<Order> getActiveOrder(const std::vector<Car>&type);
    std::pair<bool,Order> getActiveOrder(const std::string& phone);
};

#endif // DATABASEINTERFACE_H
