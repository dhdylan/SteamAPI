#ifndef STEAMWEBREQUEST_H
#define STEAMWEBREQUEST_H

#include <string>
#include <QNetworkAccessManager>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QNetworkRequest>
#include <QObject>
#include <QDebug>
#include <QObject>

class SteamWebRequest : public QObject
{
    Q_OBJECT
public:
    explicit SteamWebRequest(QObject *parent = nullptr);
    SteamWebRequest(QUrl url);
    QNetworkReply getNetworkReply();
    void sendHTTPRequest();

    QUrl url;

signals:
    void requestReady(QByteArray);

private:
    QNetworkAccessManager *manager;
    QNetworkReply::NetworkError networkReply;

    void handleNetworkReply();
};

#endif // STEAMWEBREQUEST_H
