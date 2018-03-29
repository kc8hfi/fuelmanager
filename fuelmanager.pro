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
HEADERS += about.h \
           alldata.h \
           alldatamodel.h \
           assistant.h \
           configdialog.h \
           databaseconfigpage.h \
           databasequery.h \
           datedelegate.h \
           editdate.h \
           entryform.h \
           login.h \
           mainwindow.h \
           mymodel.h \
           selectvehicledialog.h \
           sortproxy.h \
           statistics.h \
           vehicleconfigpage.h \
           vehicledisplaymodel.h \
           vehicleeditmodel.h \
    configure.h \
    configurevehicle.h
           
           
FORMS +=  about.ui \
          alldata.ui \
          loginbase.ui \
          entryform.ui \
          mainwindowbase.ui \
          statistics.ui \
    configurebase.ui \
    configurevehiclebase.ui

SOURCES += about.cpp \
           alldata.cpp \
           alldatamodel.cpp \
           assistant.cpp \
           configdialog.cpp \
           databaseconfigpage.cpp \
           databasequery.cpp \
           datedelegate.cpp \
           editdate.cpp \
           entryform.cpp \
           login.cpp \
           main.cpp \
           mainwindow.cpp \
           mymodel.cpp \
           selectvehicledialog.cpp \
           sortproxy.cpp \
           statistics.cpp \
           vehicleconfigpage.cpp \
           vehicledisplaymodel.cpp \
           vehicleeditmodel.cpp \
    configure.cpp \
    configurevehicle.cpp
           

QT += sql


lessThan(QT_MAJOR_VERSION,5): CONFIG += help
greaterThan(QT_MAJOR_VERSION, 4): QT += help

RESOURCES = resources.qrc
