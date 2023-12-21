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
    /// �����ӽ�������
    /// </summary>
    /// <returns>����0����ʾ�ɹ�</returns>
    int ProcessDownload();

    /// <summary>
    /// ��ȡ�������Url���ӣ���ƴ��
    /// </summary>
    /// <param name="pStruct">�������ص�url</param>
    /// <returns>����0����ʾ�ɹ�</returns>
    int GetUrlContent();

    QNetworkRequest* GetRequestPtr()const {
        return m_Request;
    }


public slots:
    void BeginProcess();

protected:
    /// <summary>
    /// ��ʼ����������
    /// </summary>
    /// <param name="pStruct">��������ز���</param>
    /// <returns>����0����ʾ�ɹ�</returns>
    int InitDownload();


private:
    StreamUrl* m_DownData;
    QNetworkRequest* m_Request;
};
