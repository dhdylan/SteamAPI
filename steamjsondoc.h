#ifndef STEAMJSONDOC_H
#define STEAMJSONDOC_H

#include <QObject>

class SteamJsonDoc : public QObject
{
    Q_OBJECT
public:
    explicit SteamJsonDoc(QObject *parent = nullptr);

signals:
};

#endif // STEAMJSONDOC_H
