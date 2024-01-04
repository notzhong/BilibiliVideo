#include "downloadmanage.h"
#include "ConfigValue.h"
#include "custom_define.h"
#include <QDebug>


DownloadManage::DownloadManage(void* pStream) :
    m_DownData(reinterpret_cast<pStreamUrl>(pStream)),
    QObject(nullptr)
{
    try
    {
        int result = PROCESS_SUCCESS;
        result = InitPyRelolver();
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

int DownloadManage::InitPyRelolver() {

    return PROCESS_SUCCESS;
}

int DownloadManage::ProcessDownload()
{
    for (int i = 0; i < m_DownData->UrlCount; i++)
    {
        qDebug() << __FUNCTION__ << __LINE__ << m_DownData->DownloadValue->at(i).base_url;
    }
    return PROCESS_SUCCESS;
}
