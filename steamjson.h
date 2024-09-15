#ifndef STEAMJSON_H
#define STEAMJSON_H
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>
#include <QDebug>
#include <QObject>
#include "steamgametime.h"

class SteamJson
{
public:
    static QList<SteamGameTime> tryParseJson(QByteArray);
};

#endif // STEAMJSON_H
