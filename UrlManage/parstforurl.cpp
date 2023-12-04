#include "parstforurl.h"
#include "custom_define.h"
#include <QDebug>
#include <qnetworkcookie.h>
#include <qnetworkcookiejar.h>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <qregularexpression.h>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>

ParstForUrl::ParstForUrl(pStreamUrl pUrl, int ObjectId, QObject *parent)
    : QObject(parent),
    m_pConnectUrl(pUrl),
    m_ObjectId(ObjectId),
    HtmlStr(QString()),
    m_Manager(nullptr),
    m_request(nullptr)
{
    qDebug() << "create id:" << m_ObjectId;
    ProcessInit();
}

ParstForUrl::~ParstForUrl()
{
    qDebug() << "release sucessed!!!";
    delete m_Manager;
    delete m_request;
}

QNetworkAccessManager* ParstForUrl::GetNetworkAccessManager()
{
    return m_Manager;
}

void ParstForUrl::CallProcess()
{
    ExeProcess();
}

int ParstForUrl::ExeProcess()
{
    try
    {
        if (!m_Manager || !m_request)
            throw PROCESS_FAILED;
        auto reply = m_Manager->get(*m_request);
        // 创建事件循环
        QEventLoop eventLoop;
        connect(m_Manager, &QNetworkAccessManager::finished, [&]() {
            ConnectReply(reply);
            eventLoop.quit();
            });
        PRINT_LOG(QString("run..."));
        eventLoop.exec();
    }
    catch (const int erron)
    {
        qDebug() << __FILE__ << Q_FUNC_INFO << __LINE__ << erron;
    }
    
    return PROCESS_SUCCESS;
}

int ParstForUrl::ProcessInit()
{
    try
    {
        m_Manager = new QNetworkAccessManager(this);
        m_request = new QNetworkRequest(QUrl(m_pConnectUrl->DownloadValue->value(m_ObjectId).base_url));
        if (!m_Manager || !m_request)
            throw PROCESS_FAILED;

        m_request->setHeader(QNetworkRequest::UserAgentHeader,
            m_pConnectUrl->UserAgentHeader);
        m_request->setRawHeader("Accept-Language",
            m_pConnectUrl->AcceptLanguage.toLatin1());
        m_request->setRawHeader("Host", m_pConnectUrl->Base_Host.toLatin1());

        if (!m_pConnectUrl->Base_Cookie.isEmpty()) {
            m_request->setRawHeader("Cookie", m_pConnectUrl->Base_Cookie.toLatin1());
        }

        connect(this, &ParstForUrl::PassCallProcess, this, &ParstForUrl::CallProcess);
    }
    catch (...)
    {
        qDebug() << __FILE__ << Q_FUNC_INFO << __LINE__ << "create object failed:: m_Manager:" <<
            m_Manager << " ,m_request:" << m_request;
    }
    
    return PROCESS_SUCCESS;
}

int ParstForUrl::GetUrlName()
{
    if (!HtmlStr.isEmpty())
    {
        QRegularExpression re("<title data-vue-meta=.*>(.*?)</title>");
        QRegularExpressionMatch match = re.match(HtmlStr);
        if (match.hasMatch()) {
            auto name = (QString*)(&m_pConnectUrl->DownloadValue->at(m_ObjectId).name);
            *name = match.captured(1);
            PRINT_LOG(m_pConnectUrl->DownloadValue->value(m_ObjectId).name);
        }
    }
    return PROCESS_SUCCESS;
}

int ParstForUrl::GetVideo()
{
    QRegularExpression re("<script>.*(\"video\".*]),\"audio.*</script>");
    QRegularExpressionMatch match = re.match(HtmlStr);
    if (match.hasMatch())
    {
        QString strVideo = match.captured(1);
        re.setPattern("(\"baseUrl\"+.*?),\"base_url");
        match = re.match(strVideo);
        strVideo = match.captured(1);
        QString* tempUrl = (QString*)(&m_pConnectUrl->DownloadValue->at(m_ObjectId).Video_url);
        *tempUrl = strVideo.replace("\"", "").replace(QRegExp("baseUrl:{1}"), "");
        //PRINT_LOG(m_pConnectUrl->DownloadValue->at(m_ObjectId).Video_url);
    }
    else
        return PROCESS_FAILED;
    return PROCESS_SUCCESS;
}

int ParstForUrl::GetAudio()
{
    QRegularExpression reAudio("<script>.*(\"audio\".*]),\"dolby.*</script>");
    QRegularExpressionMatch match = reAudio.match(HtmlStr);
    if (match.hasMatch())
    {
        QString strAudio = match.captured(1);
        //qDebug() << strAudio;
        reAudio.setPattern("(\"baseUrl\"+.*?),\"base_url");
        match = reAudio.match(strAudio);
        strAudio = match.captured(1);
        //qDebug() << strAudio;
        QString* tempUrl = (QString*)(&m_pConnectUrl->DownloadValue->at(m_ObjectId).Audio_url);
        *tempUrl = strAudio.replace("\"", "").replace(QRegExp("baseUrl:{1}"), "");
        PRINT_LOG(m_pConnectUrl->DownloadValue->at(m_ObjectId).Audio_url);
    }
    else
        return PROCESS_FAILED;
    return PROCESS_SUCCESS;
}


void ParstForUrl::ConnectReply(QNetworkReply* p) {
    PRINT_LOG("have data");
    if (!p)return;
    int result = PROCESS_SUCCESS;
    try
    {
        if (p->error() == QNetworkReply::NoError) {
            HtmlStr = p->readAll();
            if (!HtmlStr.isEmpty()) {
                if (PROCESS_FAILED == GetUrlName())
                    throw QString("GetUrlName is failed");
                if (PROCESS_FAILED == GetVideo())
                    throw QString("GetVideo is failed");
                if(PROCESS_FAILED == GetAudio())
                    throw QString("GetAudio is failed");
            }
            else
                throw QString("HtmlStr is null");
        }
        else
            throw QString("QNetworkReply *p have error!!!");
        p->deleteLater();
    }
    catch (const QString Errno)
    {
        qDebug() << __FILE__ << Q_FUNC_INFO << __LINE__ << "get error::"<< Errno;
    }
}