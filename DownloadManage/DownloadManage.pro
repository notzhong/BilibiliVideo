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

CONFIG(debug,debug|release){
DESTDIR = $$PWD/../lib
LIBS += -L/../bin
TARGET = DownloadManage_d
}else{
TARGET = DownloadManage
}
