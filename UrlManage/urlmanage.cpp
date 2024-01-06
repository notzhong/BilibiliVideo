#include <QDebug>
#include <qnetworkcookie.h>
#include <qnetworkcookiejar.h>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <qregularexpression.h>
#include <QFile>

#include "urlmanage.h"
#include "custom_define.h"

#include <iostream>
#include <thread>

namespace CoustomThread {
    using namespace std;
    thread t1;
};


UrlManage::UrlManage() :
    m_BaseUrl(nullptr),
    QObject(nullptr),
    HtmlStr(QString())
{
    m_cookie = QSharedPointer<QNetworkCookieJar>(new QNetworkCookieJar());
}

UrlManage::~UrlManage()
{
    if (m_BaseUrl)
        delete m_BaseUrl;

}

auto UrlManage::InitManage(void* pStruct)->int
{
    try
    {
        if (!pStruct)
            throw nullptr;
        m_BaseUrl = static_cast<StreamUrl*>(pStruct);
        m_Manager = QSharedPointer<QNetworkAccessManager>(new QNetworkAccessManager());
        m_request = QSharedPointer<QNetworkRequest>(new QNetworkRequest(QUrl(m_BaseUrl->Base_url)));

        QRegularExpression re("www\\.\\w+\\.com");
        QRegularExpressionMatch match = re.match(m_BaseUrl->Base_url);
        if (match.hasMatch())m_BaseUrl->Base_Host = match.captured(0);
        m_Manager.data()->setCookieJar(m_cookie.data());

        m_request.data()->setHeader(QNetworkRequest::UserAgentHeader,
            m_BaseUrl->UserAgentHeader.toLatin1());
        m_request.data()->setRawHeader("Accept-Language",
            m_BaseUrl->AcceptLanguage.toLatin1());
        m_request.data()->setRawHeader("Host", m_BaseUrl->Base_Host.toLatin1());
        if (!m_BaseUrl->Base_Cookie.isEmpty()) {
            m_request.data()->setRawHeader("Cookie", m_BaseUrl->Base_Cookie.toLatin1());
        }
        for each (auto v in m_request.data()->rawHeaderList())
        {
            qDebug() << v << ":" << m_request.data()->rawHeader(v);
        }

        QObject::connect(m_Manager.data(), SIGNAL(finished(QNetworkReply*)), this, SLOT(getReply(QNetworkReply*)));
    }
    catch (...)
    {
        qDebug() << "UrlManage Init failed.";
        return PROCESS_FAILED;
    }
   
    return PROCESS_SUCCESS;
}

auto UrlManage::ProcessUrl()->int
{
    auto result = PROCESS_SUCCESS;
    if (PROCESS_FAILED == GetUrlContent())
        return PROCESS_FAILED;
    if (m_BaseUrl->DownloadValue == nullptr)
    {
        CoustomThread::t1 = std::thread(&UrlManage::GetUrlCount,this);
        CoustomThread::t1.detach();
    }

    return PROCESS_SUCCESS;
}

void UrlManage::getReply(QNetworkReply*p) {
    if (!p)return;
    if (p->error() == QNetworkReply::NoError) {
        HtmlStr = QString(p->readAll());
        if (m_BaseUrl->Base_Cookie.isEmpty()) {
            auto cookies = m_cookie.data()->cookiesForUrl(m_BaseUrl->Base_url);
            QString cookie_name, cookie_value;
            for each (auto cookie in cookies)
            {
                if (!m_BaseUrl->Base_Cookie.isEmpty())
                    m_BaseUrl->Base_Cookie += " ";
                cookie_name = cookie.name();
                cookie_value = cookie.value();
                m_BaseUrl->Base_Cookie += QString("%1=%2;").arg(cookie_name).arg(cookie_value);
                qDebug() << "Cookie:" << m_BaseUrl->Base_Cookie;
            }
        }
    }
    else qDebug() << "getReply failed!!!";
    p->deleteLater();
}

void UrlManage::DestroyObject(int Id)
{
}

auto UrlManage::GetUrlContent()->int
{
    if (m_Manager.data()->get(*m_request.data()) == nullptr) {
        return PROCESS_FAILED;
    }
    return PROCESS_SUCCESS;
}

auto UrlManage::GetUrlCount() -> void
{
    while (true) {
        if (!HtmlStr.isEmpty()) {
            QRegularExpression re("<span class=\"cur-page\">\\(\\d+/(\\d+)\\)</span>");
            QRegularExpressionMatch match = re.match(HtmlStr);
            m_BaseUrl->DownloadValue = new QList<DSV>();
            m_BaseUrl->UrlCount = match.captured(1).toInt();
            if (m_BaseUrl->UrlCount > 0) {
                QString tmpUrl;
                for (int i = 1; i <= m_BaseUrl->UrlCount; i++)
                {
                    tmpUrl = m_BaseUrl->Base_url.replace(QRegExp("p=\\d+&"), QString("p=%1&").arg(i));
                    std::cout << tmpUrl.toStdString().c_str() << std::endl;
                    m_BaseUrl->DownloadValue->append({tmpUrl});
                }
                break;
            }
            else
            {
                _sleep(1000);
                continue;
            }
        }
    }
    ProcessEd();
}
