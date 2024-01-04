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

