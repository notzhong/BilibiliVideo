#pragma once

#include <QObject>

typedef struct TransferTheValueForThreads TVFT;
typedef struct TransferTheValueForThreads *pTVFT;

class DownInfoData;
class DownloadManage;
class QNetworkRequest;
class QNetworkAccessManager;

class DownLoadThread  : public QObject
{
    Q_OBJECT

public:
    DownLoadThread(QObject* parent);
    DownLoadThread(TVFT& Struct, QObject* parent = nullptr);
    ~DownLoadThread();

signals:
    void runing();

public slots:
    void DestoryThis();
    void run();

private:
    pTVFT m_pTVFT;
    DownInfoData* m_process;
    DownloadManage* m_pManage;
    QNetworkRequest* m_pRequest;
    QString url;
    QString name;
    QNetworkAccessManager* m_pQAManager;
};
