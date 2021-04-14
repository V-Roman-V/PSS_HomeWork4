#include "databaseinterface.h"

void DataBaseInterface::fillDatabase()
{
    accounts.selectSheet("Passenger");
    QXlsx::Cell* cell;
    for(int row = 2;;row++){
        accounts.selectSheet("Passenger");
        cell = accounts.cellAt(row, ACCOUNTS_COLUMNS::PHONE);
        if(cell == NULL)break;
        if(!accounts.selectSheet(cell->readValue().toString())){
            accounts.addSheet(cell->readValue().toString());
            accounts.selectSheet(cell->readValue().toString());
        }
        QXlsx::Format format;
        format.setHorizontalAlignment(QXlsx::Format::AlignHFill);
        format.setPatternBackgroundColor(QColor(Qt::GlobalColor::yellow));
        format.setShrinkToFit(true);
        accounts.write(1,1,"Orders",format);
        accounts.write(1,2,"Pinned addresses",format);
        accounts.write(1,3,"Address description",format);
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
//        std::cout<<var<<std::endl;
        if(var == phone)
            return row;
    }
    return -1;
}

People DataBaseInterface::getPerson(int row) const
{
//    if (doc.cellAt(row, COLUMNS::NAME)== NULL)return People();
    auto date = accounts.cellAt(row,ACCOUNTS_COLUMNS::DATEOFBIRTH)->readValue().toString().split("-");
    int y = date[0].toInt();
    int m = date[1].toInt();
    int d = date[2].toInt();

    int s,n;
    s = accounts.cellAt(row, ACCOUNTS_COLUMNS::PASSSERIES)->readValue().toInt();
    n = accounts.cellAt(row, ACCOUNTS_COLUMNS::PASSNUMBER)->readValue().toInt();
    return People(accounts.cellAt(row, ACCOUNTS_COLUMNS::NAME)->readValue().toString().toStdString(),
                  accounts.cellAt(row, ACCOUNTS_COLUMNS::SURNAME)->readValue().toString().toStdString(),
                  Gender::fromString(accounts.cellAt(row, ACCOUNTS_COLUMNS::GENDER)->readValue().toString().toStdString()),
                  Date(d,m,y),
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
    return Driver(getPerson(row),
                  Rating(accounts.cellAt(row, ACCOUNTS_COLUMNS::RATING)->readValue().toInt())
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
    return Passenger(getPerson(row),
                     Rating(accounts.cellAt(row, ACCOUNTS_COLUMNS::RATING)->readValue().toInt())
                     );
}

DataBaseInterface::DataBaseInterface()
    :accounts(QCoreApplication::applicationDirPath()+"/DataBase/Accounts.xlsx")
{
//    std::cout<<(QCoreApplication::applicationDirPath()+"/DataBase/Accounts.xlsx").toStdString()<<std::endl;
    bool loadDataBase = accounts.load(); // load excel file
    assert(loadDataBase);
    fillDatabase();
}


