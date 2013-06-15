#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QLinkedList>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "fminfo.h"
#include "playinfo.h"

class FMPlayer;

class PlayList : public QObject
{
    Q_OBJECT

private:
    void parseList(QByteArray &data);
    void removeList();
public:
    PlayList(QNetworkAccessManager* network_manager);
    ~PlayList();

    void loadNextList();
    void changeFM(FMInfo* playing);
    void getNextMusic();
    PlayInfo* getPlayingMusic();
    FMInfo* getPlayingFM();

private:
    QNetworkAccessManager* network_manager;
    QLinkedList<PlayInfo*> play_list;
    FMInfo* playing_fm;
    PlayInfo* playing;
    QNetworkRequest load_request;
    QNetworkReply* load_reply;
    QNetworkRequest change_request;
    QNetworkReply* change_reply;

signals:
    void loaded();

private slots:
    void playLoaded(PlayInfo* info);
    void loadNextListFinished();
    void changeFMFinished();
};

#endif // PLAYLIST_H
