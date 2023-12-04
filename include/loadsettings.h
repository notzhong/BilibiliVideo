#pragma once

#include "loadsettings_global.h"
#include <QString>

class LOADSETTINGS_EXPORT LoadSettings
{
public:
    LoadSettings();
    ~LoadSettings();
    QString GetUrl();
    QString GetCookie();
    int InitSetting();

    static LoadSettings* GetInstances();
    static int DestroyInstance();

private:
    QString url;
    QString cookie;
    static LoadSettings* Instance;
};
