#pragma once

#include <QObject>
#include <qsharedpointer.h>

#include "ConfigValue.h"

class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkCookieJar;
class QNetworkReply;

class ParstForUrl : public QObject
{
    Q_OBJECT

public:
    explicit ParstForUrl(pStreamUrl pUrl,int ObjectId, QObject *parent = nullptr);
    ~ParstForUrl();
    QNetworkAccessManager* GetNetworkAccessManager();

/// <summary>
/// 解析出返回内容的video、audio url后调用，发出信号带Object ID
/// </summary>
signals:void DestroyObject(int Id);
signals:void PassCallProcess();

public slots:
    void CallProcess();

protected:
    int ProcessInit();

private:

    /// <summary>
    /// 接收解析出来的视频链接地址
    /// </summary>
    pStreamUrl m_pConnectUrl;

    /// <summary>
    /// 设置new出的对象Id号
    /// </summary>
    int m_ObjectId;

    /// <summary>
    /// 根据传入的参数配置request后get需要的Object
    /// </summary>
    QNetworkAccessManager* m_Manager;

    /// <summary>
    /// 用于发送请求
    /// </summary>
    QNetworkRequest* m_request;

};
