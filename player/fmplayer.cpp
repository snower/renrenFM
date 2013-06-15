#include "fmplayer.h"
#include <QUrl>
#include <QFile>
#include <QNetworkRequest>
#include <QMediaContent>
#include "../renrenfm.h"

FMPlayer::FMPlayer(RenrenFm* renren_fm) : QObject()
{
    this->renren_fm=renren_fm;
    this->fm_list=NULL;
    this->init();
}

FMPlayer::~FMPlayer(){
    delete this->network_manager;
    delete this->media_player;
    delete this->fm_list;
    delete this->play_list;
}

void FMPlayer::init(){
    this->network_manager=new QNetworkAccessManager(this);
    this->media_player=new QMediaPlayer(this);
}

void FMPlayer::load(){
    this->view=renren_fm->getWindow()->getPlayerView();

    QObject::connect(this->media_player,SIGNAL(bufferStatusChanged(int)),this,SLOT(bufferStatusChanged(int)));
    QObject::connect(this->media_player,SIGNAL(positionChanged(qint64)),this,SLOT(durationChanged(qint64)));
    QObject::connect(this->media_player,SIGNAL(volumeChanged(int)),this,SLOT(volumeChanged(int)));
    QObject::connect(this->media_player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(mediaStatusChanged(QMediaPlayer::MediaStatus)));
    QObject::connect(this->media_player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(stateChanged(QMediaPlayer::State)));

    QObject::connect(this,SIGNAL(updateBufferStatus(int)),this->view,SLOT(updateBufferStatus(int)),Qt::QueuedConnection);
    QObject::connect(this,SIGNAL(updatePlayerInfo(PlayInfo*)),this->view,SLOT(updatePlayerInfo(PlayInfo*)),Qt::QueuedConnection);
    QObject::connect(this,SIGNAL(updateDuration(int,int)),this->view,SLOT(updateDuration(int,int)),Qt::QueuedConnection);
    QObject::connect(this,SIGNAL(updateVolume(int)),this->view,SLOT(updateVolume(int)),Qt::QueuedConnection);
    QObject::connect(this,SIGNAL(updateStatus(int)),this->view,SLOT(updatePlayerStatus(int)),Qt::QueuedConnection);

    QObject::connect(this->view,SIGNAL(playStatusChanged(bool)),this,SLOT(playStatusChange(bool)));
    QObject::connect(this->view,SIGNAL(nexted()),this,SLOT(nextPlay()));
    QObject::connect(this->view,SIGNAL(durationChnanged(int)),this,SLOT(durationChange(int)));
    QObject::connect(this->view,SIGNAL(volumeChanged(int)),this,SLOT(volumeChange(int)));

    this->loadFMList();
    this->media_player->setVolume(70);
}

void FMPlayer::loadFMList(){
    this->fm_list=new FMList(this->network_manager,this->renren_fm->getWindow()->getView()->getList());
    QObject::connect(this->fm_list,SIGNAL(FMListLoaded()),this,SLOT(FMListLoaded()));
    QObject::connect(this->fm_list,SIGNAL(played(FMInfo*)),this,SLOT(play(FMInfo*)));
    this->fm_list->load();
}

void FMPlayer::FMListLoaded(){
    this->play_list=new PlayList(this->network_manager);
    QObject::connect(this->play_list,SIGNAL(loaded()),this,SLOT(playListLoaded()));
    this->play();
}

void FMPlayer::playListLoaded(){
    PlayInfo* info=this->play_list->getPlayingMusic();
    if(info==NULL) return;
    emit this->updatePlayerInfo(info);
    this->media_player->setMedia(QUrl::fromLocalFile("cache\\"+info->src_name));
    this->media_player->play();
    qDebug()<<info->src_name;
}

void FMPlayer::play(FMInfo *fm){
    this->media_player->stop();
    if(fm==NULL){
        this->play_list->changeFM(this->fm_list->getFM());
    }
    else{
        this->play_list->changeFM(fm);
    }
}

void FMPlayer::bufferStatusChanged(int percentFilled){
    emit this->updateBufferStatus(percentFilled);
}

void FMPlayer::durationChanged(qint64 duration){
    emit this->updateDuration(duration/1000,this->media_player->duration()/1000);
}

void FMPlayer::volumeChanged(int volume){
    emit this->updateVolume(volume);
}

void FMPlayer::playStatusChange(bool status){
    if(status){
        this->media_player->play();
    }else{
        this->media_player->pause();
    }
}

void FMPlayer::nextPlay(){
    this->media_player->stop();
    this->play_list->getNextMusic();
}

void FMPlayer::durationChange(int duration){
}

void FMPlayer::volumeChange(int volume){
    this->media_player->setVolume(volume);
}

void FMPlayer::mediaStatusChanged(QMediaPlayer::MediaStatus status){
    switch(status){
    case QMediaPlayer::EndOfMedia:
    case QMediaPlayer::InvalidMedia:
    case QMediaPlayer::UnknownMediaStatus:
    case QMediaPlayer::NoMedia:
        this->play_list->getNextMusic();
        break;
    default:
        return;
    }
}

void FMPlayer::stateChanged(QMediaPlayer::State state){
    switch (state) {
    case QMediaPlayer::StoppedState:
        emit this->updateStatus(0);
        break;
    case QMediaPlayer::PlayingState:
        emit this->updateStatus(1);
        break;
    case QMediaPlayer::PausedState:
        emit this->updateStatus(2);
        break;
    default:
        emit this->updateStatus(0);
        break;
    }
}
