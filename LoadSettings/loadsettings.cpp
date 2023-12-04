#include "loadsettings.h"
#include "custom_define.h"
#include <QSettings>
#include <QFile>
#include <QDebug>

LoadSettings::LoadSettings():
    url(QString()),
    cookie(QString())
{
    try
    {
        auto result = InitSetting();
        if (result)
            throw result;
    }
    catch (const int result)
    {
        qDebug() << "init Settings failed erron:" << result;
    }
}

LoadSettings::~LoadSettings()
{
}

QString LoadSettings::GetUrl()
{
    return url;
}

QString LoadSettings::GetCookie()
{
    return cookie;
}

int LoadSettings::InitSetting()
{
    QSettings file(QString("./config.ini"), QSettings::IniFormat);

    if (QFile::exists("config.ini")) {
        if (file.contains("value/url"))
            url = file.value("value/url").toString();
        else 
            file.setValue("value/url", QString());

        if (file.contains("value/cookie"))
            cookie = file.value("value/cookie").toString();
        else
            file.setValue("value/cookie", QString());
    }
    else {
        QFile setting("./config.ini");
        if (setting.open(QIODevice::WriteOnly))
        {
            qDebug() << "file is created!";
            setting.close();
        }
        InitSetting();
        return PROCESS_FAILED;
    }

    return PROCESS_SUCCESS;
}

LoadSettings* LoadSettings::GetInstances()
{
    if (!Instance)
        Instance = new LoadSettings;
    return Instance;
}

int LoadSettings::DestroyInstance()
{
    if (Instance) {
        delete Instance;
        Instance = nullptr;
    }
    else return PROCESS_FAILED;
    return PROCESS_SUCCESS;
}


LoadSettings* LoadSettings::Instance = nullptr;