#include "downloadmanage.h"
#include "ConfigValue.h"
#include "custom_define.h"
#include "downloadthread.h"
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qnetworkrequest.h>

#include <iostream>
#include <thread>
#include <mutex>



DownloadManage::DownloadManage(void* pStream) :
    m_DownData(reinterpret_cast<pStreamUrl>(pStream)),
    m_Request(nullptr),
    QObject(nullptr)
{
    try
    {
        int result = PROCESS_SUCCESS;
        result = InitDownload();
        if (result)
            throw result;
    }
    catch (const int result)
    {
        qDebug() << __FILE__ << Q_FUNC_INFO << __LINE__ << "error:" << result;
    }
}

DownloadManage::~DownloadManage()
{
}

void DownloadManage::BeginProcess() {
    ProcessDownload();
}

int DownloadManage::InitDownload()
{
    m_Request = new QNetworkRequest();
    if (!m_Request)
        return PROCESS_FAILED;
    if (!m_DownData->UserAgentHeader.isEmpty())
        m_Request->setHeader(QNetworkRequest::UserAgentHeader, m_DownData->UserAgentHeader);
    if (!m_DownData->AcceptLanguage.isEmpty())
        m_Request->setRawHeader("Accept-Language", m_DownData->AcceptLanguage.toLatin1());
    if (!m_DownData->Base_Cookie.isEmpty())
        m_Request->setRawHeader("Cookie", m_DownData->Base_Cookie.toLatin1());
    if (!m_DownData->Base_Host.isEmpty())
        m_Request->setRawHeader("Host", m_DownData->Base_Host.toLatin1());
    return PROCESS_SUCCESS;
}

int DownloadManage::ProcessDownload()
{
    if (!m_Request)
        return PROCESS_FAILED;
    for (int i = 0; i < 1/*m_DownData->UrlCount*/; i++)
    {
        TVFT Value = TVFT{ this, StreamClass::VEDIO, m_DownData->DownloadValue->at(i) };
        auto p = (new DownLoadThread(Value));
        emit p->runing();
        Value = TVFT{ this, StreamClass::AUDIO, m_DownData->DownloadValue->at(i) };
        p = (new DownLoadThread(Value));
        emit p->runing();
    }
    return PROCESS_SUCCESS;
}

int DownloadManage::GetUrlContent()
{

    return PROCESS_SUCCESS;
}
