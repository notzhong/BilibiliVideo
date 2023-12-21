#include "ConfigValue.h"
#include "downloadthread.h"
#include "downinfodata.h"
#include "downloadmanage.h"
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>


DownLoadThread::DownLoadThread(QObject *parent)
    : QObject(parent)
{}

DownLoadThread::DownLoadThread(TVFT & Struct, QObject * parent)
    : QObject(parent)
{
    m_pManage = reinterpret_cast<DownloadManage*>(Struct.pDManager);
    m_pQAManager = new QNetworkAccessManager(this);
    m_pTVFT = (pTVFT)malloc(sizeof(TVFT)); //new TVFT(Struct);
    memcpy_s(m_pTVFT, sizeof(TVFT), &Struct, sizeof(TVFT));
    auto pData = Struct.DSV;
    m_process = new DownInfoData(m_pQAManager, this);
    m_pRequest = m_pManage->GetRequestPtr();
    url = (Struct.Id == StreamClass::VEDIO ? pData.Video_url : pData.Audio_url);
    connect(this, &DownLoadThread::runing, this, &DownLoadThread::run);
}

void DownLoadThread::DestoryThis() {
    delete this;
}

void DownLoadThread::run() {
    m_process->ProcessExe(m_pRequest, url, m_pTVFT->DSV.name, m_pTVFT->Id);
}

DownLoadThread::~DownLoadThread()
{
    delete m_process;
    free(m_pTVFT);
    m_process = NULL;
    m_pTVFT = NULL;
    terminate();
}
