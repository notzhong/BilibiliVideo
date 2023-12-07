#pragma once

#include <QThread>

typedef struct TransferTheValueForThreads TVFT;
typedef struct TransferTheValueForThreads *pTVFT;

class DownInfoData;
class DownloadManage;

class DownLoadThread  : public QThread
{
    Q_OBJECT

public:
    void run();
    DownLoadThread(QObject* parent);
    DownLoadThread(TVFT& Struct, QObject* parent);
    ~DownLoadThread();

private:
    pTVFT m_pTVFT;
    DownInfoData* m_process;
    DownloadManage* m_pManage;
    QString url;
};
