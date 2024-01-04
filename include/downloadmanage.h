#pragma once
#include <QObject>

struct StreamUrl;

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

protected:
    /// <summary>
    /// 初始化Python 解释器
    /// </summary>
    /// <param name="pStruct">null</param>
    /// <returns>返回0，表示成功</returns>
    int InitPyRelolver();


private:
    StreamUrl* m_DownData;
};
