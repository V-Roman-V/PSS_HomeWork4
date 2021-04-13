#include "databaseinterface.h"
#include <iostream>

#include "xlsxdocument.h"
//#include "xlsxchartsheet.h"
//#include "xlsxcellrange.h"
//#include "xlsxchart.h"
//#include "xlsxrichstring.h"
//#include "xlsxworkbook.h"
using namespace QXlsx;

DataBaseInterface::DataBaseInterface()
{
    QXlsx::Document xlsx;
    xlsx.write("A1", "Hello Qt!"); // write "Hello Qt!" to cell(A,1). it's shared string.
    xlsx.saveAs("Test.xlsx"); // save the document as 'Test.xlsx'
}

DataBaseInterface::~DataBaseInterface()
{
}
