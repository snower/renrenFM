#ifndef RPLAYER_H
#define RPLAYER_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QLabel>
#include "rbutton.h"
#include "rcdplayer.h"
#include "rtimershaft.h"
#include "rvolume.h"

class PlayInfo;

class RPlayer : public QWidget
{
    Q_OBJECT
private:
    void init();
    void initButton();
    void initMusicInfo();
    void painterBackGround(QPainter* painter);

protected:
    virtual void paintEvent(QPaintEvent *);

public:
    explicit RPlayer(QWidget *parent = 0);
    ~RPlayer();

private:
    QImage* bg_pannel;
    QImage* bg_radio;
    RCdPlayer* cd_player;
    RButton* button_love;
    RButton* button_share;
    RButton* button_no;
    RButton* button_next;
    QLabel* label_fm_title;
    QLabel* label_album;
    QLabel* label_title;
    RTimerShaft* timer_shaft;
    RVolume* volume;
    bool status;
    
signals:
    void durationChnanged(int duration);
    void volumeChanged(int volume);
    void playStatusChanged(bool status);
    void nexted();

public slots:
    void changeStatus(bool status);
    void changeToSideBar(bool pos);
    void changeToPlayre(bool pos);

    void updatePlayerStatus(int status);
    void updatePlayerInfo(PlayInfo* info);
    void updateBufferStatus(int percentFilled);
    void updateDuration(int duration,int duration_long);
    void updateVolume(int volume);

private slots:
    void playBtnClicked(bool status);
    void nextBtnClicked();
    void timerShaftClicked(int duration);
    void volumeClicked(int volume);
};

#endif // RPLAYER_H
