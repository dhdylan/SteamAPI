#ifndef STEAMGAMETIME_H
#define STEAMGAMETIME_H
#include <QJsonObject>
#include "steamgame.h"

class SteamGameTime
{
public:
    SteamGameTime();
    SteamGame steamGame;
    int playtime2Weeks;
    int playtimeForever;
};

#endif // STEAMGAMETIME_H
