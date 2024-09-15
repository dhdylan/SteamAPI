#include "steamwebrequest.h"

SteamWebRequest::SteamWebRequest(QObject *parent)
    : QObject{parent}
{}


SteamWebRequest::SteamWebRequest(QUrl url)
{
    this->url = url;
    manager = new QNetworkAccessManager();
}

void SteamWebRequest::sendHTTPRequest()
{
    QNetworkRequest request(url);
    // Perform the GET request
    QNetworkReply *reply = manager->get(request);

    // Connect the finished signal to the handleNetworkReply slot
    connect(reply, &QNetworkReply::finished, this, &SteamWebRequest::handleNetworkReply);
}

void SteamWebRequest::handleNetworkReply()
{
    // Get the QNetworkReply sender
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (reply)
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            // Success: read the data
            response = reply->readAll();
            emit requestReady(response);
        } else {
            // Error: display the error message
            qDebug() << "Error:" << reply->errorString();
        }

        // Cleanup
        reply->deleteLater();
    }
}
