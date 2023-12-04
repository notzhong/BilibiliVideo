#pragma once

#include <QObject>
#include "custom_define.h"

class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;



class DownInfoData  : public QObject
{
    Q_OBJECT

public:
    DownInfoData(QNetworkAccessManager* manager, QObject *parent = nullptr);
    ~DownInfoData();
    int ProcessExe(QNetworkRequest* pRequest, QString& Url, QString& name, StreamClass& ID);

public slots:
    void GetReply(QNetworkReply* p);

protected:
    int GetVedioData(QNetworkReply* p);
    int GetAudioData(QNetworkReply* p);

private:
    QNetworkAccessManager* m_manager;
    StreamClass m_ID;
};
