#include "databaseinterface.h"
//#include <iostream>

int DataBaseInterface::findPerson(const std::string& phone)
{
    QXlsx::Cell* cell;
    for(int row = 2;;row++){
        cell = doc.cellAt(row, COLUMNS::PHONE);
        if(cell == NULL)break;
        std::string var = cell->readValue().toString().toStdString();
//        std::cout<<var<<std::endl;
        if(var == phone)
            return row;
    }
    return -1;
}

People DataBaseInterface::getPerson(int row)
{
    auto date = doc.cellAt(row,COLUMNS::DATEOFBIRTH)->readValue().toString().split("-");
    int y = date[0].toInt();
    int m = date[1].toInt();
    int d = date[2].toInt();

    int s,n;
    s = doc.cellAt(row, COLUMNS::PASSSERIES)->readValue().toInt();
    n = doc.cellAt(row, COLUMNS::PASSNUMBER)->readValue().toInt();
    return People(doc.cellAt(row, COLUMNS::NAME)->readValue().toString().toStdString(),
                  doc.cellAt(row, COLUMNS::SURNAME)->readValue().toString().toStdString(),
                  Gender::fromString(doc.cellAt(row, COLUMNS::GENDER)->readValue().toString().toStdString()),
                  Date(d,m,y),
                  Passport(s,n),
                  doc.cellAt(row, COLUMNS::PHONE)->readValue().toString().toStdString()
                 );
}

int DataBaseInterface::findDriver(const std::string& phone)
{
    doc.selectSheet("Driver");
    return findPerson(phone);
}

Driver DataBaseInterface::getDriver(int row)
{
    doc.selectSheet("Driver");
    return Driver(getPerson(row),
                  Rating(doc.cellAt(row, COLUMNS::RATING)->readValue().toInt())
                  );
}

int DataBaseInterface::findPassenger(const std::string& phone)
{
    doc.selectSheet("Passenger");
    return findPerson(phone);
}

Passenger DataBaseInterface::getPassenger(int row)
{
    doc.selectSheet("Passenger");
    return Passenger(getPerson(row),
                     Rating(doc.cellAt(row, COLUMNS::RATING)->readValue().toInt())
                     );
}

DataBaseInterface::DataBaseInterface()
    :doc(":/Accounts.xlsx")
{
    bool loadDataBase = doc.load(); // load excel file
    assert(loadDataBase);
}


