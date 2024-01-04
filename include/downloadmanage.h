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
    /// �����ӽ�������
    /// </summary>
    /// <returns>����0����ʾ�ɹ�</returns>
    int ProcessDownload();

protected:
    /// <summary>
    /// ��ʼ��Python ������
    /// </summary>
    /// <param name="pStruct">null</param>
    /// <returns>����0����ʾ�ɹ�</returns>
    int InitPyRelolver();


private:
    StreamUrl* m_DownData;
};
