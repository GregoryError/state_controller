#include "networkworker.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <iostream>
#include <QByteArray>
#include <QUrl>


networkworker::networkworker(QObject* parent) : QObject (parent)
{
    manager = new QNetworkAccessManager(parent);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}

void networkworker::goUrl(const QString& r_str)
{

  //  manager->get(QNetworkRequest(QUrl("http://stat.vbg/cgi-bin/ramon/mac.pl?a=cab&ip=250.150")));


    request.setUrl(QUrl("https://fcm.googleapis.com/fcm/send"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Key=AAAAzCqCOsY:APA91bENRWfnh7l6QOTGeI6Q6g2bp1uz_UKlQAlgUlaASPmY0mh8w5Gkcrl5uFJ1g4ROoyKA2IJiR0-YC7Wb5D-1o9MJvfITQKJl2NT5HFz_aXfGDKMgnyJw-LXQ7BE2A-Ziv3tR0yjP"));
    request.setPriority(QNetworkRequest::HighPriority);

    QJsonObject json
    {
        {"to", "dTcuDhwDsj8:APA91bEcEFt3Ic4vxzXz0-iv1hUcsiFuDz-HVa_o_7D4Rs7XTD6-7IGk5-Hmb0t0onvkYSWT7yy8ZBY-HaimlT3y7TAwG6q9jyTtcERA0H0G80q2Y8YqcOzNItNOrvHccMSAG7FT9jsB"},
        //{"to", "/topics/all"},
        {"notification",
            QJsonObject{ {"title", "Сетевое событие"}, {"body", r_str}, {"sound", "default"}} }
    };


    reply = manager->post(request, QJsonDocument(json).toJson());
//    manager->get(QNetworkRequest(QUrl("http://stat.vbg/cgi-bin/ramon/mac.pl?a=cab&ip=")));


}

bool networkworker::isFinished()
{
    bool t_finished = finished;
    finished = false;
    return t_finished;
}

void networkworker::replyFinished(QNetworkReply *)
{
    finished = true;
    std::cout << "Reply errors: " << reply->errorString().toStdString();
    std::cout << "Reply result: " << reply->readAll().toStdString() << '\n';
}

void networkworker::slotReadyRead()
{
    std::cout << "Slot readyRead: " << reply->readAll().toStdString() << '\n';
}
























