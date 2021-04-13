#include <iostream>
#include "Interfaces/databaseinterface.h"
#include "Interfaces/commoninterface.h"

using namespace std;

int main()
{
    CommonInterface cI;
    cI.start();
    return 0;
}
