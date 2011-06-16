#-------------------------------------------------
#
# Project created by QtCreator 2011-06-01T17:37:36
#
#-------------------------------------------------

QT       += core gui network

TARGET = Galcon_01
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    network.cpp \
    parser.cpp \
    message.cpp \
    log.cpp \
    game.cpp \
    DialogConnect.cpp \
    Planet.cpp \
    Fleet.cpp \
    Map.cpp \
    Player.cpp \
    DialogCountdown.cpp \
    DialogMessage.cpp \
    sources.cpp \
    planetview.cpp \
    fleetview.cpp \
    graphics.cpp \
    UserNameValidator.cpp \
    AddressValidator.cpp

HEADERS  += mainwindow.h \
    network.h \
    parser.h \
    message.h \
    log.h \
    game.h \
    DialogConnect.h \
    Planet.h \
    Fleet.h \
    Map.h \
    Player.h \
    DialogCountdown.h \
    DialogMessage.h \
    sources.h \
    planetview.h \
    fleetview.h \
    graphics.h \
    UserNameValidator.h \
    AddressValidator.h

FORMS    += mainwindow.ui

RESOURCES += \
    image.qrc
