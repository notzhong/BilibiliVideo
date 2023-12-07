#include "ConfigValue.h"
#include "downloadthread.h"
#include "downinfodata.h"
#include "downloadmanage.h"
#include <iostream>
#include <mutex>

using namespace std;

namespace CoustomThread {
    mutex mtx;
}

//    thread t1, t2;
//    void ThreadProcess(TVFT& pValue) {
//        lock_guard<mutex>lock(mtx);
//        DownloadManage* pManage = reinterpret_cast<DownloadManage*>(pValue.pDManager);
//        auto pData = pValue.DSV;
//        auto process = new DownInfoData(*pManage);
//        auto url = (pValue.Id == StreamClass::VEDIO ? pData.Video_url : pData.Audio_url);
//        process->ProcessExe(pManage->GetRequestPtr(), url, pData.name, pValue.Id);
//        delete process;
//    }
//};


DownLoadThread::DownLoadThread(QObject *parent)
    : QThread(parent)
{}

DownLoadThread::DownLoadThread(TVFT & Struct, QObject * parent)
{
    m_pManage = reinterpret_cast<DownloadManage*>(Struct.pDManager);
    m_pTVFT = &Struct;
    auto pData = Struct.DSV;
    m_process = new DownInfoData(*m_pManage);
    url = (Struct.Id == StreamClass::VEDIO ? pData.Video_url : pData.Audio_url);
}

void DownLoadThread::run() {
    lock_guard<mutex>lock(CoustomThread::mtx);
    m_process->ProcessExe(m_pManage->GetRequestPtr(), url, m_pTVFT->DSV.name, m_pTVFT->Id);
}

DownLoadThread::~DownLoadThread()
{
    delete m_process;
    terminate();
}
