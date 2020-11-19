#ifndef NETWORKWORKER_H
#define NETWORKWORKER_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>


class networkworker : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager *manager;
    QNetworkReply* reply;
    QNetworkRequest request;
public:
    networkworker(QObject *parent = nullptr);
    void goUrl(const QString& r_str);
    bool finished = false;
    bool isFinished();
public slots:

    void replyFinished(QNetworkReply* reply);
    void slotReadyRead();


signals:
//    void finished(QNetworkReply*);
};

#endif // NETWORKWORKER_H
