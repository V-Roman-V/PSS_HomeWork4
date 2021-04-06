TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt
QT += core

SOURCES += \
        Additional_classes/address.cpp \
        Additional_classes/date.cpp \
        Additional_classes/order.cpp \
        Additional_classes/passport.cpp \
        Additional_classes/peoplegenerator.cpp \
        Car_classes/car.cpp \
        Enumerations/cartype.cpp \
        Enumerations/dayofweek.cpp \
        Enumerations/month.cpp \
        Enumerations/rating.cpp \
        Enumerations/status.cpp \
        People_classes/driver.cpp \
        People_classes/passenger.cpp \
        People_classes/people.cpp \
        main.cpp

HEADERS += \
    Additional_classes/address.h \
    Additional_classes/date.h \
    Additional_classes/order.h \
    Additional_classes/passport.h \
    Additional_classes/peoplegenerator.h \
    Car_classes/car.h \
    Enumerations/cartype.h \
    Enumerations/dayofweek.h \
    Enumerations/month.h \
    Enumerations/rating.h \
    Enumerations/status.h \
    People_classes/driver.h \
    People_classes/passenger.h \
    People_classes/people.h
