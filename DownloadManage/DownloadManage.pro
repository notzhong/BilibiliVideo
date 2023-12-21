QT += core network

CONFIG += c++17
TEMPLATE = lib
DEFINES += DOWNLOADMANAGE_LIB


INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include

HEADERS += \
    ../include/ConfigValue.h \
    ../include/custom_define.h \
    ../include/downinfodata.h \
    ../include/downloadmanage.h \
    ../include/downloadmanage_global.h

SOURCES += \
    downinfodata.cpp \
    downloadmanage.cpp

DESTDIR = $$PWD/../lib

CONFIG(debug,debug|release){
TARGET = DownloadManage_d
}else{
TARGET = DownloadManage
}
