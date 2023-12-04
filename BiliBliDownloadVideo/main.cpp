#include <QtCore/QCoreApplication>
#include <QDebug>
#include "urlmanage.h"
#include "loadsettings.h"
#include "downloadmain.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    UrlManage test;
    QString url = LoadSettings::GetInstances()->GetUrl();
    QString cookie = LoadSettings::GetInstances()->GetCookie();
    QSharedPointer<StreamUrl>in_test = QSharedPointer<StreamUrl>(new StreamUrl(url,cookie));
    
    if (!url.isEmpty())
    {
        test.InitManage(in_test.data());
        test.ProcessUrl();
        QSharedPointer<DownloadMain>test2 = QSharedPointer<DownloadMain>(new DownloadMain(in_test.data()));
        QObject::connect(&test, &UrlManage::ProcessEd, [&]() {
            test2.data()->ProcessEx();
            });
        
    }
    else qDebug() << "url is null!!!";
    

    return a.exec();
}
