#ifndef PLAYINFO_H
#define PLAYINFO_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#define PLAY_RELOAD_COUNT 3

class PlayInfo : public QObject
{
    Q_OBJECT

private:
    void init();
    void loadMusic();
    void loadAlbum();
    QString getName(QString name,QString type);
    void writeToFile(QString name,QByteArray &data);

public:
    PlayInfo(int id,QString name,QString artistName,int artistId,QString src,int duration,QString albumSrc,QString albumName,int albumId,QString lyric,bool fav);
    ~PlayInfo();

    void load(QNetworkAccessManager* network_manager);
    bool isLoaded();
    bool isError();

public:
    int id;
    QString name;
    QString artistName;
    int artistId;
    QString src;
    int duration;
    QString albumSrc;
    QString albumName;
    int albumId;
    QString lyric;
    bool fav;
    QString src_name;
    QString albumSrc_name;

private:
    QNetworkAccessManager* network_manager;
    QNetworkRequest music_request;
    QNetworkReply* music_reply;
    QNetworkRequest album_request;
    QNetworkReply* album_reply;
    bool music_loaded;
    bool album_loaded;
    bool error;
    int load_music_count;
    int load_album_count;

signals:
    void loaded(PlayInfo* info);

private slots:
    void musicLoaded();
    void albumLoaded();
};

#endif // PLAYINFO_H
