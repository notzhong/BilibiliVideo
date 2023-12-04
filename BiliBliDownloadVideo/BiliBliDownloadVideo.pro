QT += core

CONFIG += c++17 console

HEADERS += \
    ../include/ConfigValue.h \
    ../include/custom_define.h \
    ../include/downinfodata.h \
    ../include/downloadmanage.h \
    ../include/loadsettings.h \
    ../include/parstforurl.h \
    ../include/urlmanage.h

SOURCES += \
    main.cpp

win32: LIBS += -L$$PWD/../lib/ -lDownloadManage_d
win32: LIBS += -L$$PWD/../lib/ -lLoadSettings_d
win32: LIBS += -L$$PWD/../lib/ -lUrlManage_d

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include

