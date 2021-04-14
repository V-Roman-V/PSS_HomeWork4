#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include <string>
#include "xlsxdocument.h"
#include "People_classes/people.h"
#include "People_classes/passenger.h"
#include "People_classes/driver.h"
#include <QCoreApplication>

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
        RATING
    };

    QXlsx::Document accounts;

    void fillDatabase();

    int findPerson(const std::string& phone)const;
    People getPerson(int p) const;
protected:
    DataBaseInterface();

    int findPassenger(const std::string& phone);
    Passenger getPassenger(int p);

    int findDriver(const std::string& phone);
    Driver getDriver(int p);
};

#endif // DATABASEINTERFACE_H
