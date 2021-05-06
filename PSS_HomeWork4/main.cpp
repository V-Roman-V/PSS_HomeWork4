#include <iostream>
#include "Interfaces/databaseinterface.h"
#include "Interfaces/commoninterface.h"

#include <QCoreApplication>

using namespace std;

int main(int argc, char * argv[])
{
    QCoreApplication app(argc, argv);

    CommonInterface cI;
    cI.start();

    return 0;
}
