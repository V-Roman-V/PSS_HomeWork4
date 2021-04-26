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

std::vector<Order> DataBaseInterface::getActiveOrder(CarType type)
{
    std::vector<Order> orders;
    accounts.selectSheet("Active_orders");
    for(int row = 2;;row++){
        auto *cell = accounts.cellAt(row, ORDERS_COLUMNS::ORDERNUMBER);
        if(cell == NULL)break;
        Order order;
        order.car    = CarType(accounts.read(row,ORDERS_COLUMNS::CARTYPE).toInt());
        if(order.car.number() != type.number()) continue;

        order.number = accounts.read(row,ORDERS_COLUMNS::ORDERNUMBER).toInt();
        order.from   = accounts.read(row,ORDERS_COLUMNS::ADDRESSFROM).toString().toStdString();
        order.to     = accounts.read(row,ORDERS_COLUMNS::ADDRESSTO).toString().toStdString();
        order.price  = accounts.read(row,ORDERS_COLUMNS::PRICE).toDouble();
        order.time   = accounts.read(row,ORDERS_COLUMNS::TIME).toTime();
        order.date   = accounts.read(row,ORDERS_COLUMNS::DATE).toDate();
        orders.push_back(order);
    }
    return orders;
}

std::pair<bool,Order> DataBaseInterface::getActiveOrder(std::string phone)
{
    Order order;
    accounts.selectSheet("Active_orders");
    for(int row = 2;;row++){
        auto *cell = accounts.cellAt(row, ORDERS_COLUMNS::A_Pass);
        if(cell == NULL)break;
        if(cell->value().toString().toStdString() != phone) continue;
        order.car    = CarType(accounts.read(row,ORDERS_COLUMNS::CARTYPE).toInt());
        order.number = accounts.read(row,ORDERS_COLUMNS::ORDERNUMBER).toInt();
        order.from   = accounts.read(row,ORDERS_COLUMNS::ADDRESSFROM).toString().toStdString();
        order.to     = accounts.read(row,ORDERS_COLUMNS::ADDRESSTO).toString().toStdString();
        order.price  = accounts.read(row,ORDERS_COLUMNS::PRICE).toDouble();
        order.time   = accounts.read(row,ORDERS_COLUMNS::TIME).toTime();
        order.date   = accounts.read(row,ORDERS_COLUMNS::DATE).toDate();
        return std::make_pair(true,order);
    }
    return std::make_pair(false,order);
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
        order.number = accounts.read(row+1,ORDERS_COLUMNS::ORDERNUMBER).toInt();
        order.from   = accounts.read(row+1,ORDERS_COLUMNS::ADDRESSFROM).toString().toStdString();
        order.to     = accounts.read(row+1,ORDERS_COLUMNS::ADDRESSTO).toString().toStdString();
        order.car    = CarType(accounts.read(row+1,ORDERS_COLUMNS::CARTYPE).toInt());
        order.price  = accounts.read(row+1,ORDERS_COLUMNS::PRICE).toDouble();
        order.time   = accounts.read(row+1,ORDERS_COLUMNS::TIME).toTime();
        order.date   = accounts.read(row+1,ORDERS_COLUMNS::DATE).toDate();
        orders.push_back(order);
    }

    accounts.selectSheet("Passenger");
    Passenger pass(User(person,orders,Rating(accounts.cellAt(row, ACCOUNTS_COLUMNS::RATING)->readValue().toInt())),
                   addresses
                   );
    auto pair = getActiveOrder(pass.getPhone());
    if(pair.first)
        pass.setCurrentOrder(pair.second);
    return pass;
}

void DataBaseInterface::savePinAddress(const std::string &phone, const Address &address)
{
    accounts.selectSheet(QString::fromStdString(phone));
    for(int row=2;;row++){;
        auto *cell = accounts.cellAt(row, PASSENGER_COLUMNS::PINNEDADDR);
        if(cell != NULL)continue;
        accounts.write(row,PASSENGER_COLUMNS::PINNEDADDR,QString::fromStdString(address));
        if(address.name().size()>0)
            accounts.write(row,PASSENGER_COLUMNS::ADDRNAME,QString::fromStdString(address.name()));
        break;
    }
    accounts.save();
}

void DataBaseInterface::closeActiveOrder(const Order &order, const std::string& Dphone)
{
    std::string Pphone = getActiveOrderPhone(order.number);
    deleteActiveOrder(order);
    accounts.selectSheet("Orders");
    for(int row=2;;row++){;
        auto *cell = accounts.cellAt(row, ORDERS_COLUMNS::ORDERNUMBER);
        if(cell != NULL)continue;
        accounts.write(row,ORDERS_COLUMNS::ORDERNUMBER,order.number);
        accounts.write(row,ORDERS_COLUMNS::ADDRESSFROM,QString::fromStdString(order.from));
        accounts.write(row,ORDERS_COLUMNS::ADDRESSTO  ,QString::fromStdString(order.to));
        accounts.write(row,ORDERS_COLUMNS::CARTYPE    ,order.car.number());
        accounts.write(row,ORDERS_COLUMNS::PRICE      ,order.price);
        accounts.write(row,ORDERS_COLUMNS::TIME       ,order.time);
        accounts.write(row,ORDERS_COLUMNS::DATE       ,static_cast<QDate>(order.date));
        break;
    }

    accounts.selectSheet(QString::fromStdString(Pphone));
    for(int row=2;;row++){;
        auto *cell = accounts.cellAt(row, PASSENGER_COLUMNS::ORDERS);
        if(cell != NULL)continue;
        accounts.write(row,PASSENGER_COLUMNS::ORDERS, order.number);
        break;
    }

    accounts.selectSheet(QString::fromStdString(Dphone));
    for(int row=2;;row++){;
        auto *cell = accounts.cellAt(row, DRIVER_COLUMNS::ORDERS_D);
        if(cell != NULL)continue;
        accounts.write(row,DRIVER_COLUMNS::ORDERS_D, order.number);
        break;
    }

    accounts.save();
}

void DataBaseInterface::takeActiveOrder(const Order &order)
{
    accounts.selectSheet("Active_orders");
    for(int row=2;;row++){;
        auto *cell = accounts.cellAt(row, ORDERS_COLUMNS::ORDERNUMBER);
        if(cell == NULL)break;
        if(cell->value().toInt() == order.number){
            accounts.write(row,ORDERS_COLUMNS::A_Status, Status(1).number());
            break;
        }
    }
    accounts.save();
}

void DataBaseInterface::saveActiveOrder(const Order &order,const std::string phone)
{
    accounts.selectSheet("Active_orders");
    for(int row=2;;row++){;
        auto *cell = accounts.cellAt(row, ORDERS_COLUMNS::ORDERNUMBER);
        if(cell != NULL && cell->value() != "")continue;
        accounts.write(row,ORDERS_COLUMNS::ORDERNUMBER,order.number);
        accounts.write(row,ORDERS_COLUMNS::ADDRESSFROM,QString::fromStdString(order.from));
        accounts.write(row,ORDERS_COLUMNS::ADDRESSTO  ,QString::fromStdString(order.to));
        accounts.write(row,ORDERS_COLUMNS::CARTYPE    ,order.car.number());
        accounts.write(row,ORDERS_COLUMNS::PRICE      ,order.price);
        accounts.write(row,ORDERS_COLUMNS::TIME       ,order.time);
        accounts.write(row,ORDERS_COLUMNS::DATE       ,static_cast<QDate>(order.date));
        accounts.write(row,ORDERS_COLUMNS::A_Pass     ,QString::fromStdString(phone));
        accounts.write(row,ORDERS_COLUMNS::A_Status   ,Status(0).number());
        break;
    }
    accounts.save();
}

void DataBaseInterface::deleteActiveOrder(const Order &order)
{
    accounts.selectSheet("Active_orders");
    accounts.cellAt(2,1)->value().clear();
    accounts.cellAt(2,2)->value().clear();

    int row=2;
    bool del = false;
    for(;;row++){
        auto *cell = accounts.cellAt(row, ORDERS_COLUMNS::ORDERNUMBER);
        if(cell == NULL)break;
        if(cell->value().toInt() != order.number) continue;
        accounts.write(row,ORDERS_COLUMNS::ORDERNUMBER,"");
        accounts.write(row,ORDERS_COLUMNS::ADDRESSFROM,"");
        accounts.write(row,ORDERS_COLUMNS::ADDRESSTO,"");
        accounts.write(row,ORDERS_COLUMNS::CARTYPE,"");
        accounts.write(row,ORDERS_COLUMNS::DATE,"");
        accounts.write(row,ORDERS_COLUMNS::PRICE,"");
        accounts.write(row,ORDERS_COLUMNS::TIME,"");
        accounts.write(row,ORDERS_COLUMNS::A_Pass,"");
        accounts.write(row,ORDERS_COLUMNS::A_Status,"");
        del = true;
        break;
    }
    row++;
    for(;del;row++){
        auto *cell = accounts.cellAt(row, ORDERS_COLUMNS::ORDERNUMBER);
        if(cell == NULL)break;
        accounts.write(row-1,ORDERS_COLUMNS::ORDERNUMBER,accounts.read(row,ORDERS_COLUMNS::ORDERNUMBER));
        accounts.write(row-1,ORDERS_COLUMNS::ADDRESSFROM,accounts.read(row,ORDERS_COLUMNS::ADDRESSFROM));
        accounts.write(row-1,ORDERS_COLUMNS::ADDRESSTO,accounts.read(row,ORDERS_COLUMNS::ADDRESSTO));
        accounts.write(row-1,ORDERS_COLUMNS::CARTYPE,accounts.read(row,ORDERS_COLUMNS::CARTYPE));
        accounts.write(row-1,ORDERS_COLUMNS::DATE,accounts.read(row,ORDERS_COLUMNS::DATE));
        accounts.write(row-1,ORDERS_COLUMNS::PRICE,accounts.read(row,ORDERS_COLUMNS::PRICE));
        accounts.write(row-1,ORDERS_COLUMNS::TIME,accounts.read(row,ORDERS_COLUMNS::TIME));
        accounts.write(row-1,ORDERS_COLUMNS::A_Pass,accounts.read(row,ORDERS_COLUMNS::A_Pass));
        accounts.write(row-1,ORDERS_COLUMNS::A_Status,accounts.read(row,ORDERS_COLUMNS::A_Status));

        accounts.write(row,ORDERS_COLUMNS::ORDERNUMBER,"");
        accounts.write(row,ORDERS_COLUMNS::ADDRESSFROM,"");
        accounts.write(row,ORDERS_COLUMNS::ADDRESSTO,"");
        accounts.write(row,ORDERS_COLUMNS::CARTYPE,"");
        accounts.write(row,ORDERS_COLUMNS::DATE,"");
        accounts.write(row,ORDERS_COLUMNS::PRICE,"");
        accounts.write(row,ORDERS_COLUMNS::TIME,"");
        accounts.write(row,ORDERS_COLUMNS::A_Pass,"");
        accounts.write(row,ORDERS_COLUMNS::A_Status,"");
    }
    accounts.save();
}

std::pair<bool,Status> DataBaseInterface::getOrderStatus(int number)
{
    accounts.selectSheet("Active_orders");
    for(int row=2;;row++){;
        auto *cell = accounts.cellAt(row, ORDERS_COLUMNS::ORDERNUMBER);
        if(cell == NULL)break;
        if(cell->value().toInt() == number)
            return std::make_pair(true,Status(accounts.read(row, ORDERS_COLUMNS::A_Status).toInt()));
    }
    return std::make_pair(false,Status(0));
}

std::string DataBaseInterface::getActiveOrderPhone(int number)
{
    accounts.selectSheet("Active_orders");
    for(int row=2;;row++){;
        auto *cell = accounts.cellAt(row, ORDERS_COLUMNS::ORDERNUMBER);
        if(cell == NULL)break;
        if(cell->value().toInt() == number)
            return accounts.read(row, ORDERS_COLUMNS::A_Pass).toString().toStdString();
    }
    return "";
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
    accounts.selectSheet("Active_orders");
    int num = accounts.read(2,ORDERS_COLUMNS::A_LASTORDER).toInt();
    accounts.write(2,ORDERS_COLUMNS::A_LASTORDER,num+1);
    accounts.save();
    return num;
}


