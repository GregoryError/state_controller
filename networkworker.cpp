#include "networkworker.h"
#include <QtNetwork/QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <iostream>
#include <QByteArray>

networkworker::networkworker(QObject* parent) : QObject (parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}

void networkworker::goUrl()
{
        QNetworkRequest request;
        request.setUrl(QUrl("https://fcm.googleapis.com/fcm/send"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setRawHeader(QByteArray("Authorization"), QByteArray("Key=AAAAzCqCOsY:APA91bENRWfnh7l6QOTGeI6Q6g2bp1uz_UKlQAlgUlaASPmY0mh8w5Gkcrl5uFJ1g4ROoyKA2IJiR0-YC7Wb5D-1o9MJvfITQKJl2NT5HFz_aXfGDKMgnyJw-LXQ7BE2A-Ziv3tR0yjP"));
        request.setPriority(QNetworkRequest::HighPriority);



        QJsonObject json
        {
            {"to", "euT9G0904c4:APA91bHPmVuZT6idBc8WV9piPv7oA939j_XKUhcggTTMYvFGSHTp703fhNqidiEoRqmrj2DICeTwNf9BSCuR64q0xpJhnDyDNupukAFI3AKsuybfsSZq1AXutm2vuRhxEJ3ZH3Ucn_ND"},
            {"notification",
                QJsonObject{ {"title", "Finally!"}, {"body", "some test text"}, {"sound", "default"}}}
        };


         auto res = manager->post(request, QJsonDocument(json).toJson());

         qDebug() << "Errors: " << res->errorString();

}

void networkworker::replyFinished(QNetworkReply *)
{
        std::cout << "Reply result: " << reply->readAll().toStdString() << '\n';
}


