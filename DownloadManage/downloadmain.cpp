#include "downloadmain.h"
#include "downloadmanage.h"

DownloadMain::DownloadMain(void* pStream) :
    m_main(nullptr)
{
    if (pStream)
        m_main = new DownloadManage(pStream);
}

DownloadMain::~DownloadMain()
{
    if (m_main)
        delete m_main;
}

int DownloadMain::ProcessEx()
{
    if (m_main != nullptr)
        m_main->ProcessDownload();
    return 0;
}
