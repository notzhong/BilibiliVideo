#include "downinfodata.h"
#include "ConfigValue.h"
#include <qdebug.h>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <qnetworkrequest.h>
#include <QEventLoop>

DownInfoData::DownInfoData(QNetworkAccessManager* manager, QObject *parent)
    : QObject(parent),
    m_manager(manager),
    m_ID(StreamClass::VEDIO),
    m_DownName(QString())
{
}

DownInfoData::~DownInfoData()
{
    delete m_manager;
    m_manager = nullptr;
}

int DownInfoData::ProcessExe(QNetworkRequest* pRequest, QString& Url, QString& name, StreamClass& ID)
{
    m_ID = ID;
    m_DownName = name;
    pRequest->setUrl(QUrl(Url));
    if (m_manager && pRequest)
    {
        auto reply = m_manager->get(*pRequest);
        // 创建事件循环
        QEventLoop eventLoop;
        connect(m_manager, &QNetworkAccessManager::finished, [&]() {
            GetReply(reply);
            eventLoop.quit();
            });
        eventLoop.exec();
    }
    else
        return PROCESS_FAILED;
    return PROCESS_SUCCESS;
}

int DownInfoData::GetVedioData(QNetworkReply* p)
{
    qDebug() << __FILE__ << Q_FUNC_INFO << __LINE__ << " p:" << p;
    return PROCESS_SUCCESS;
}

int DownInfoData::GetAudioData(QNetworkReply* p)
{
    qDebug() << __FILE__ << Q_FUNC_INFO << __LINE__ << " p:" << p;
    return PROCESS_SUCCESS;
}


void DownInfoData::GetReply(QNetworkReply* p) {
    int result = PROCESS_SUCCESS;

    if (p->error() == QNetworkReply::NoError) {
        switch (m_ID)
        {
        case StreamClass::VEDIO:
            result = GetVedioData(p);
            break;
        case StreamClass::AUDIO:
            result = GetAudioData(p);
            break;
        default:
            break;
        }
        if (result)
            qDebug() << __FILE__ << Q_FUNC_INFO << __LINE__ << (m_ID == StreamClass::VEDIO ? QString("vedio error") : QString("audio error"));
    }
    else
        qDebug() << __FILE__ << Q_FUNC_INFO << __LINE__ << p->errorString();

    emit GetReplyed();
}