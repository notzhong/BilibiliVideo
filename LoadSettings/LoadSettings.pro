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

CONFIG(debug,debug|release){
DESTDIR = $$PWD/../lib
TARGET = LoadSettings_d
}else{
TARGET = LoadSettings
}