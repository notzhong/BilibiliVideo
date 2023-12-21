QT += core

CONFIG += c++17
TEMPLATE = lib
DEFINES += LOADSETTINGS_LIB


INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include

HEADERS += \
    ../include/ConfigValue.h \
    ../include/custom_define.h \
    ../include/loadsettings.h \
    ../include/loadsettings_global.h

SOURCES += \
    loadsettings.cpp

DESTDIR = $$PWD/../lib

CONFIG(debug,debug|release){
TARGET = LoadSettings_d
}else{
TARGET = LoadSettings
}