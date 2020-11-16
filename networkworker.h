#ifndef NETWORKWORKER_H
#define NETWORKWORKER_H
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>


class networkworker : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager *manager;
    QNetworkReply* reply;
public:
    networkworker(QObject* parent);
public slots:
    void goUrl();
    void replyFinished(QNetworkReply*);
};

#endif // NETWORKWORKER_H
