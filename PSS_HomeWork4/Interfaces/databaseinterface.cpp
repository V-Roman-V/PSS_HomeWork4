#include "databaseinterface.h"
#include <QDebug>
#include <iostream>


void DataBaseInterface::fillDatabase()
{
    // used to generate people pages
    accounts.selectSheet("Passenger");
    QXlsx::Cell* cell;
    for(int row = 2;;row++){
        accounts.selectSheet("Passenger");
        cell = accounts.cellAt(row, ACCOUNTS_COLUMNS::PHONE);
        if(cell == NULL)break;
        if(accounts.selectSheet(cell->readValue().toString())) continue;

        accounts.addSheet(cell->readValue().toString());
        accounts.selectSheet(cell->readValue().toString());
        QXlsx::Format format;
        format.setHorizontalAlignment(QXlsx::Format::AlignHFill);
        format.setPatternBackgroundColor(QColor(Qt::GlobalColor::yellow));
        format.setShrinkToFit(true);
        accounts.write(1,1,"Orders",format);
        accounts.write(1,2,"Pinned addresses",format);
        accounts.write(1,3,"Address description",format);
    }
    accounts.selectSheet("Driver");
    for(int row = 2;;row++){
        accounts.selectSheet("Driver");
        cell = accounts.cellAt(row, ACCOUNTS_COLUMNS::PHONE);
        if(cell == NULL)break;
        if(accounts.selectSheet(cell->readValue().toString())) continue;

        accounts.addSheet(cell->readValue().toString());
        accounts.selectSheet(cell->readValue().toString());
        QXlsx::Format format;
        format.setHorizontalAlignment(QXlsx::Format::AlignHFill);
        format.setPatternBackgroundColor(QColor(Qt::GlobalColor::yellow));
        format.setShrinkToFit(true);
        accounts.write(1,1,"Orders",format);
        accounts.write(1,2,"Car model",format);
        accounts.write(1,3,"Car type",format);
        accounts.write(1,4,"Car number",format);
        accounts.write(1,5,"Car color",format);
    }
    accounts.save();
}

int DataBaseInterface::findPerson(const std::string& phone) const
{
    QXlsx::Cell* cell;
    for(int row = 2;;row++){
        cell = accounts.cellAt(row, ACCOUNTS_COLUMNS::PHONE);
        if(cell == NULL)break;
        std::string var = cell->readValue().toString().toStdString();
        if(var == phone)
            return row;
    }
    return -1;
}

People DataBaseInterface::getPerson(int row) const
{
    int s,n;
    s = accounts.cellAt(row, ACCOUNTS_COLUMNS::PASSSERIES)->readValue().toInt();
    n = accounts.cellAt(row, ACCOUNTS_COLUMNS::PASSNUMBER)->readValue().toInt();
    return People(accounts.cellAt(row, ACCOUNTS_COLUMNS::NAME)->readValue().toString().toStdString(),
                  accounts.cellAt(row, ACCOUNTS_COLUMNS::SURNAME)->readValue().toString().toStdString(),
                  Gender::fromString(accounts.cellAt(row, ACCOUNTS_COLUMNS::GENDER)->readValue().toString().toStdString()),
                  Date(accounts.cellAt(row,ACCOUNTS_COLUMNS::DATEOFBIRTH)->readValue().toDate()),
                  Passport(s,n),
                  accounts.cellAt(row, ACCOUNTS_COLUMNS::PHONE)->readValue().toString().toStdString()
                 );
}

int DataBaseInterface::findDriver(const std::string& phone)
{
    accounts.selectSheet("Driver");
    return findPerson(phone);
}

Driver DataBaseInterface::getDriver(int row)
{
    // TODO get Drivers
    accounts.selectSheet("Driver");
    People person = getPerson(row);
    accounts.selectSheet(QString::fromStdString(person.getPhone()));
    std::vector<int> ordersNum;
    for(int row = 2;;row++){
        auto cell = accounts.cellAt(row, DRIVER_COLUMNS::ORDERS_D);
        if(cell == NULL)break;
        ordersNum.push_back(cell->value().toInt());
    }

    sort(ordersNum.begin(),ordersNum.end());
    qDebug()<<ordersNum;
    std::vector<Order> orders;
    accounts.selectSheet("Orders");
    for(auto row:ordersNum){
        Order order;
        order.number = row+1;
        order.from   = accounts.read(row+1,ORDERS_COLUMNS::ADDRESSFROM).toString().toStdString();
        order.to     = accounts.read(row+1,ORDERS_COLUMNS::ADDRESSTO).toString().toStdString();
        order.car    = CarType(accounts.read(row+1,ORDERS_COLUMNS::CARTYPE).toInt());
        order.price  = accounts.read(row+1,ORDERS_COLUMNS::PRICE).toDouble();
        order.time   = accounts.read(row+1,ORDERS_COLUMNS::TIME).toTime();
        order.date   = accounts.read(row+1,ORDERS_COLUMNS::DATE).toDate();
        orders.push_back(order);
        std::cout<<order;
    }

    accounts.selectSheet(QString::fromStdString(person.getPhone()));
    Car car;
    car.model = accounts.read(2,DRIVER_COLUMNS::CARMODEL_D).toString().toStdString();
    car.type  = CarType(accounts.read(2,DRIVER_COLUMNS::CARTYPE_D).toInt());
    car.coordinates  = QPointF(0,0);
    car.color = accounts.read(2,DRIVER_COLUMNS::CARCOLOR_D).toString().toStdString();
    car.number = accounts.read(2,DRIVER_COLUMNS::CARNUBER_D).toString().toStdString();
    car.setBottles(4);
    accounts.selectSheet("Driver");
    return Driver(User(person,orders,Rating(accounts.cellAt(row, ACCOUNTS_COLUMNS::RATING)->readValue().toInt())),
                  car
                  );
}

int DataBaseInterface::findPassenger(const std::string& phone)
{
    accounts.selectSheet("Passenger");
    return findPerson(phone);
}

Passenger DataBaseInterface::getPassenger(int row)
{
    accounts.selectSheet("Passenger");
    People person = getPerson(row);
    accounts.selectSheet(QString::fromStdString(person.getPhone()));
    std::vector<int> ordersNum;
    std::vector<Address> addresses;
    for(int row = 2;;row++){
        auto cell = accounts.cellAt(row, PASSENGER_COLUMNS::ORDERS);
        if(cell == NULL)break;
        ordersNum.push_back(cell->value().toInt());
    }
    for(int row = 2;;row++){
        auto cell = accounts.cellAt(row, PASSENGER_COLUMNS::PINNEDADDR);
        if(cell == NULL)break;
        Address address = cell->value().toString().toStdString();
        auto name = accounts.cellAt(row, PASSENGER_COLUMNS::ADDRNAME);
        if(name != NULL)
            address.setName( name->value().toString().toStdString());

        addresses.push_back(address);
    }

    sort(ordersNum.begin(),ordersNum.end());
    std::vector<Order> orders;
    accounts.selectSheet("Orders");
    for(auto row:ordersNum){
        Order order;
        order.number = row+1;
        order.from   = accounts.read(row+1,ORDERS_COLUMNS::ADDRESSFROM).toString().toStdString();
        order.to     = accounts.read(row+1,ORDERS_COLUMNS::ADDRESSTO).toString().toStdString();
        order.car    = CarType(accounts.read(row+1,ORDERS_COLUMNS::CARTYPE).toInt());
        order.price  = accounts.read(row+1,ORDERS_COLUMNS::PRICE).toDouble();
        order.time   = accounts.read(row+1,ORDERS_COLUMNS::TIME).toTime();
        order.date   = accounts.read(row+1,ORDERS_COLUMNS::DATE).toDate();
        orders.push_back(order);
    }

    accounts.selectSheet("Passenger");
    return Passenger(User(person,orders,Rating(accounts.cellAt(row, ACCOUNTS_COLUMNS::RATING)->readValue().toInt())),
                     addresses
                     );
}

DataBaseInterface::DataBaseInterface()
    :accounts(QCoreApplication::applicationDirPath()+"/DataBase/Accounts.xlsx")
{
    bool loadDataBase = accounts.load(); // load excel file
    assert(loadDataBase);
//    fillDatabase();
}

int DataBaseInterface::getNextOrderNumber()
{
    // TODO
    return -1;
}


