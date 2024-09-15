#include "steamjson.h"

QList<SteamGameTime> SteamJson::tryParseJson(QByteArray jsonByteArray)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonByteArray);

    if(jsonDocument.isNull())
    {
        qDebug() << "jsonDocument parse failed.";
    }

    QJsonObject jsonObj = jsonDocument.object();
    QJsonObject responseObject = jsonObj["response"].toObject();
    QJsonArray gamesArray = responseObject["games"].toArray();
    QList<SteamGameTime> steamGameTimes(gamesArray.size());
    // Iterate through the array and access each game's data
    for (int i=0; i<gamesArray.size(); i++)
    {
        QJsonObject gameObj = gamesArray.at(i).toObject();
        SteamGame steamGame;
        steamGame.appID = gameObj["appid"].toInt();
        steamGame.imageURL = gameObj["img_icon_url"].toString();
        steamGame.name = gameObj["name"].toString();
        SteamGameTime sgt;
        sgt.steamGame = steamGame;
        sgt.playtime2Weeks = gameObj["playtime_2weeks"].toInt();
        sgt.playtimeForever = gameObj["playtime_forever"].toInt();
        steamGameTimes[i] = sgt;
    }
    return steamGameTimes;
}
