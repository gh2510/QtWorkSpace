#-------------------------------------------------
#
# Project created by QtCreator 2017-02-27T10:07:53
#
#-------------------------------------------------

QT       += core gui
QT       += network sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BeaThread
TEMPLATE = app


SOURCES += main.cpp\
        mythreadwidget.cpp \
    myudprecv.cpp \
    captureimage.cpp \
    capturethread.cpp \
    connection.cpp

HEADERS  += mythreadwidget.h \
    myudprecv.h \
    captureimage.h \
    capturethread.h \
    connection.h

FORMS    += mythreadwidget.ui \
    capturedialog.ui
