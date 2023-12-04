QT += core

CONFIG += c++17 console

HEADERS += \
    ../include/ConfigValue.h \
    ../include/custom_define.h \
    ../include/downloadmain.h \
    ../include/loadsettings.h
    ../include/urlmanage.h

SOURCES += \
    main.cpp
    
DESTDIR = $$PWD/../bin

CONFIG(debug,debug|release){

win32: LIBS += -L$$PWD/../lib/ -lDownloadManage_d
win32: LIBS += -L$$PWD/../lib/ -lLoadSettings_d
win32: LIBS += -L$$PWD/../lib/ -lUrlManage_d

TARGET = BiliBliDownloadVideo_d
}else{
win32: LIBS += -L$$PWD/../lib/ -lDownloadManage
win32: LIBS += -L$$PWD/../lib/ -lLoadSettings
win32: LIBS += -L$$PWD/../lib/ -lUrlManage

TARGET = BiliBliDownloadVideo
}



INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include

