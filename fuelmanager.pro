######################################################################
# Automatically generated by qmake (2.01a) Mon Mar 8 18:14:24 2010
######################################################################
TEMPLATE = app
TARGET = fuelmanager
DEPENDPATH += .
INCLUDEPATH += .

OBJECTS_DIR = build

isEmpty(PREFIX){
 PREFIX = $$(PREFIX)
}
isEmpty(PREFIX){
 PREFIX = /usr/local
}
target.path = $$PREFIX/bin
INSTALLS += target

VERSION = 0.4.2
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# Input
HEADERS += configure.h \
    configurevehicle.h \
    mainwindow.h \
    query.h \
    sqlite.h \
    testwidget.h \
    vehicledisplaymodel.h \
    selectvehicle.h \
    entryform.h \
    about.h \
    alldata.h \
    alldatamodel.h


FORMS += configurebase.ui \
    configurevehiclebase.ui \
    mainwindowbase.ui \
    testwidget.ui \
    selectvehicle.ui \
    entryform.ui \
    about.ui \
    alldata.ui


SOURCES += configure.cpp \
    configurevehicle.cpp \
    main.cpp \
    mainwindow.cpp \
    query.cpp \
    sqlite.cpp \
    testwidget.cpp \
    vehicledisplaymodel.cpp \
    selectvehicle.cpp \
    entryform.cpp \
    about.cpp \
    alldata.cpp \
    alldatamodel.cpp
           
QT += sql testlib


lessThan(QT_MAJOR_VERSION,5): CONFIG += help
greaterThan(QT_MAJOR_VERSION, 4): QT += help

RESOURCES = resources.qrc
