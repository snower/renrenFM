#ifndef FMPLAYER_H
#define FMPLAYER_H

#include <QNetworkAccessManager>
#include <QMediaPlayer>
#include "fmlist.h"
#include "playlist.h"
#include "../ui/rplayer.h"

class RenrenFm;

class FMPlayer : public QObject
{
    Q_OBJECT
private:
    void init();
    void loadFMList();
public:
    FMPlayer(RenrenFm* renren_fm);
    ~FMPlayer();

    void load();

private:
    RenrenFm* renren_fm;
    QNetworkAccessManager* network_manager;
    QMediaPlayer* media_player;
    FMList* fm_list;
    PlayList* play_list;
    RPlayer* view;

signals:
    void updateStatus(int status);
    void updatePlayerInfo(PlayInfo* info);
    void updateBufferStatus(int percentFilled);
    void updateDuration(int duration,int duration_long);
    void updateVolume(int volume);

public slots:
    void FMListLoaded();
    void playListLoaded();
    void play(FMInfo* fm=NULL);

    void playStatusChange(bool status);
    void nextPlay();
    void durationChange(int duration);
    void volumeChange(int volume);

private slots:
    void bufferStatusChanged(int percentFilled);
    void durationChanged(qint64 duration);
    void volumeChanged(int volume);
    void mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void stateChanged(QMediaPlayer::State state);
};

#endif // FMPLAYER_H
