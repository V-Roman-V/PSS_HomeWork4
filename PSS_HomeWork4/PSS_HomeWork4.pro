TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

QT += core

# QXlsx code for Application Qt project
QXLSX_PARENTPATH=./QXlsx/   # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./QXlsx/header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./QXlsx/source/  # current QXlsx source path is ./source/
include(./QXlsx.pri)

SOURCES += \
        Additional_classes/address.cpp \
        Additional_classes/car.cpp \
        Additional_classes/date.cpp \
        Additional_classes/order.cpp \
        Additional_classes/passport.cpp \
        Enumerations/cartype.cpp \
        Enumerations/dayofweek.cpp \
        Enumerations/gender.cpp \
        Enumerations/month.cpp \
        Enumerations/paytype.cpp \
        Enumerations/persontype.cpp \
        Enumerations/rating.cpp \
        Enumerations/status.cpp \
        Interfaces/commoninterface.cpp \
        Interfaces/databaseinterface.cpp \
        People_classes/driver.cpp \
        People_classes/passenger.cpp \
        People_classes/people.cpp \
        People_classes/user.cpp \
        main.cpp

HEADERS += \
    Additional_classes/address.h \
    Additional_classes/car.h \
    Additional_classes/date.h \
    Additional_classes/order.h \
    Additional_classes/passport.h \
    DataBaseInterface/databaseinterface.h \
    Enumerations/cartype.h \
    Enumerations/dayofweek.h \
    Enumerations/gender.h \
    Enumerations/month.h \
    Enumerations/paytype.h \
    Enumerations/persontype.h \
    Enumerations/rating.h \
    Enumerations/status.h \
    Interfaces/commoninterface.h \
    Interfaces/databaseinterface.h \
    People_classes/driver.h \
    People_classes/passenger.h \
    People_classes/people.h \
    People_classes/user.h

