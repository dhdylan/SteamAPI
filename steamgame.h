#ifndef STEAMGAME_H
#define STEAMGAME_H
#include <QString>

class SteamGame
{
public:
    SteamGame();
    int appID;
    QString name;
    QString imageURL;
};

#endif // STEAMGAME_H
