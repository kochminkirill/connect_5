TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        participant.cpp \
        pointxy.cpp \
        support_functions.cpp

HEADERS += \
    constants.h \
    participant.h \
    pointxy.h \
    support_functions.h \
    vectors.h
