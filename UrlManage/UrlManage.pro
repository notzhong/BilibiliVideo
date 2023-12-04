QT += core network

CONFIG += c++17
TEMPLATE = lib
DEFINES += URLMANAGE_LIB


INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include

HEADERS += \
    ../include/ConfigValue.h \
    ../include/custom_define.h \
    ../include/urlmanage.h \
    ../include/parstforurl.h \
    ../include/urlmanage_global.h

SOURCES += \
    parstforurl.cpp \
    urlmanage.cpp

CONFIG(debug,debug|release){
DESTDIR = $$PWD/../lib
TARGET = UrlManage_d
}else{
TARGET = UrlManage
}