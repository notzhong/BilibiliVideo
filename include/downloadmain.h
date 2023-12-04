#pragma once
#include "downloadmanage_global.h"
class DownloadManage;

class DOWNLOADMANAGE_EXPORT DownloadMain
{
public:
    DownloadMain(void* pStream);
    ~DownloadMain();
    int ProcessEx();
private:
    DownloadManage* m_main;
};
