#pragma once
#include <QObject>

struct StreamUrl;
class QNetworkAccessManager;
class QNetworkRequest;
class DownInfoData;

class DownloadManage  : public QObject
{
    Q_OBJECT

public:
    DownloadManage(void *pStream);
    DownloadManage(DownloadManage&) = delete;
    ~DownloadManage();

    /// <summary>
    /// 对链接进行下载
    /// </summary>
    /// <returns>返回0，表示成功</returns>
    int ProcessDownload();

    /// <summary>
    /// 获取链接里的Url链接，并拼接
    /// </summary>
    /// <param name="pStruct">传入下载的url</param>
    /// <returns>返回0，表示成功</returns>
    int GetUrlContent();

    QNetworkRequest* GetRequestPtr()const {
        return m_Request;
    }


public slots:
    void BeginProcess();

protected:
    /// <summary>
    /// 初始化下载内容
    /// </summary>
    /// <param name="pStruct">传入的下载参数</param>
    /// <returns>返回0，表示成功</returns>
    int InitDownload();


private:
    StreamUrl* m_DownData;
    QNetworkRequest* m_Request;
};
