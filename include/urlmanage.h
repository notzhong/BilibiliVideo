#pragma once

#include <qsharedpointer.h>
#include <QMap>

#include "urlmanage_global.h"
#include "ConfigValue.h"
#include "parstforurl.h"

class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkCookieJar;



class URLMANAGE_EXPORT UrlManage : public QObject
{
    Q_OBJECT

public:
    UrlManage();
    ~UrlManage();
    /// <summary>
    /// 初始化发送的header内容
    /// </summary>
    /// <param name="pStruct">is Struct StreamUrl</param>
    /// <returns>0表示成功，-1 failed</returns>
    auto InitManage(void* pStruct)->int;

    /// <summary>
    /// 处理解析传入的url，拿到相应的视频链接基本地址
    /// </summary>
    /// <returns>0 is successful, -1 is failed</returns>
    auto ProcessUrl()->int;

signals:
    void ProcessEd();

public slots:
    void getReply(QNetworkReply*p);
    void DestroyObject(int Id);

protected:
    auto GetUrlContent()->int;
    auto GetUrlCount()->void;
    auto ParseUrl()->int;

private:
    pStreamUrl m_BaseUrl;
    QMap<int, ParstForUrl*>M_Connect;
    QSharedPointer<QNetworkAccessManager>m_Manager;
    QSharedPointer<QNetworkRequest>m_request;
    QSharedPointer<QNetworkCookieJar> m_cookie;
    QString HtmlStr;
};
