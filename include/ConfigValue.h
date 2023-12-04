#ifndef CONFIGVALUE_H
#define CONFIGVALUE_H

#include <QList>
#include "custom_define.h"

typedef struct DownloadStreamValue DSV;

/// <summary>
/// 传递数据内容
/// m_url   传递的链接
/// m_name  链接的名称
/// m_pStream   接收的链接内容数据
/// </summary>
typedef struct StreamUrl
{
    QString Base_url;           /// 基础链接
    QString Base_name;          /// 链接名称，一般空
    QString Base_Cookie;        /// cookie信息
    QString Base_Host;          /// 存储HOST地址
    QString UserAgentHeader;    /// UserAgentHeader
    QString AcceptLanguage;     /// Language
    int UrlCount;               /// 链接数量


    QList<DSV>* DownloadValue;            ///下载内容的链接名称
    StreamUrl(QString url, QString cookie = QString(), QString name = QString(), void* Stream = nullptr) :
        Base_url(url),
        Base_name(name),
        DownloadValue(NULL),
        Base_Cookie(cookie),
        UrlCount(0),
        UserAgentHeader(QString()),
        AcceptLanguage(QString())
    {
        UserAgentHeader = "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/119.0";
        AcceptLanguage = "zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2";
    };

    ~StreamUrl() {};
}*pStreamUrl;


/// <summary>
/// 调用下载bilibili对应的视频(video_url)、音频(audio_url)链接
/// </summary>
struct DownloadStreamValue
{
    QString name;           ///链接视频名称
    QString base_url;       ///链接
    QString Video_url;      ///视频链接
    QString Audio_url;      ///音频链接
};


#define PRINT_LOG(log) qDebug() << __FILE__ << Q_FUNC_INFO << __LINE__ << log;


typedef struct TransferTheValueForThreads {
    void* pDManager;
    StreamClass Id;
    DownloadStreamValue DSV;
}*pTVFT, TVFT;

#endif // !CONFIGVALUE_H