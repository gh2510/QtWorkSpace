#-------------------------------------------------
#
# Project created by QtCreator 2017-08-19T10:02:38
#
#-------------------------------------------------

QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VAttemperServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    attemperpage.cpp \
    configparse.cpp \
    combatposition.cpp \
    screen.cpp \
    attemper.cpp \
    roleselect.cpp \
    role.cpp \
    attemperform.cpp

HEADERS  += mainwindow.h \
    attemperpage.h \
    configparse.h \
    UserDataType.h \
    combatposition.h \
    screen.h \
    attemper.h \
    roleselect.h \
    role.h \
    attemperform.h

FORMS    += mainwindow.ui \
    attemperpage.ui \
    roleselect.ui \
    attemperform.ui

RESOURCES += \
    qtres.qrc
