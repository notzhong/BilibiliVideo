#include "downloadmanage.h"
#include "ConfigValue.h"
#include "custom_define.h"
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qnetworkrequest.h>

#include <iostream>
#include <thread>
#include <mutex>



DownloadManage::DownloadManage(void*pStream) :
    m_DownData(reinterpret_cast<pStreamUrl>(pStream)),
    m_Manager(nullptr),
    m_Request(nullptr),
    m_pDownData(nullptr),
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
    m_Manager = new QNetworkAccessManager();
    m_Request = new QNetworkRequest();
    if (!m_Manager || !m_Request)
        return PROCESS_FAILED;
    if (!m_DownData->UserAgentHeader.isEmpty())
        m_Request->setHeader(QNetworkRequest::UserAgentHeader, m_DownData->UserAgentHeader);
    if (!m_DownData->AcceptLanguage.isEmpty())
        m_Request->setRawHeader("Accept-Language", m_DownData->AcceptLanguage.toLatin1());
    if(!m_DownData->Base_Cookie.isEmpty())
        m_Request->setRawHeader("Cookie", m_DownData->Base_Cookie.toLatin1());
    if(!m_DownData->Base_Host.isEmpty())
        m_Request->setRawHeader("Host", m_DownData->Base_Host.toLatin1());
    //m_pDownData = new DownInfoData(m_Manager);
    if (!m_pDownData)
        return PROCESS_FAILED;
    return PROCESS_SUCCESS;
}

int DownloadManage::ProcessDownload()
{
    if (!m_Manager || !m_Request)
        return PROCESS_FAILED;
    for (int i = 0; i < 1/*m_DownData->UrlCount*/; i++)
    {
        TVFT Value = TVFT{ this, StreamClass::VEDIO, m_DownData->DownloadValue->at(i) };
        
    }
    return PROCESS_SUCCESS;
}

int DownloadManage::GetUrlContent()
{

    return PROCESS_SUCCESS;
}
