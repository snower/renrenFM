#include "playlist.h"
#include <QByteArray>
#include <QVariant>
#include <QVariantMap>
#include "json.h"
#include "fmplayer.h"

PlayList::PlayList(QNetworkAccessManager* network_manager) : QObject()
{
    this->network_manager=network_manager;
    this->playing_fm=NULL;
    this->playing=NULL;
    this->load_request=QNetworkRequest();
    this->load_reply=NULL;
    this->change_request=QNetworkRequest();
    this->change_reply=NULL;
}

PlayList::~PlayList(){
    this->removeList();
}

void PlayList::loadNextList(){
    this->load_request.setUrl(QUrl("http://fm.renren.com/fm/song/next?radioId="+this->playing_fm->id+"&radioType=0"));
    this->load_reply=this->network_manager->get(this->load_request);
    QObject::connect(this->load_reply,SIGNAL(finished()),this,SLOT(loadNextListFinished()));
}

void PlayList::changeFM(FMInfo* playing){
    if(this->playing_fm!=NULL){
        this->playing_fm->changeStatus(false);
    }
    this->playing_fm=playing;
    this->playing_fm->changeStatus(true);
    this->change_request.setUrl(QUrl("http://fm.renren.com/fm/radio/change?radioId="+this->playing_fm->id+"&radioType=0&isUrlParamVisit=true&songId=0"));
    this->change_reply=this->network_manager->get(this->change_request);
    QObject::connect(this->change_reply,SIGNAL(finished()),this,SLOT(changeFMFinished()));
}

void PlayList::getNextMusic(){
    if(this->playing!=NULL){
        this->play_list.removeOne(this->playing);
        delete this->playing;
        this->playing=NULL;
    }
    QLinkedListIterator<PlayInfo*> iterator(this->play_list);
    while(iterator.hasNext()){
        PlayInfo* info=iterator.next();
        if(info->isLoaded()){
            this->playing=info;
            emit this->loaded();
            return;
        }
        if(info->isError()){
            this->play_list.removeOne(info);
            delete info;
        }
    }
    if(this->play_list.count()<=1){
        this->loadNextList();
    }
}

void PlayList::loadNextListFinished(){
    QByteArray data=this->load_reply->readAll();
    this->parseList(data);
    QLinkedListIterator<PlayInfo*> iterator(this->play_list);
    while(iterator.hasNext()){
        PlayInfo* info=iterator.next();
        QObject::connect(info,SIGNAL(loaded(PlayInfo*)),this,SLOT(playLoaded(PlayInfo*)));
        info->load(this->network_manager);
    }
}

void PlayList::changeFMFinished(){
    QByteArray data=this->change_reply->readAll();
    this->parseList(data);
    QLinkedListIterator<PlayInfo*> iterator(this->play_list);
    while(iterator.hasNext()){
        PlayInfo* info=iterator.next();
        QObject::connect(info,SIGNAL(loaded(PlayInfo*)),this,SLOT(playLoaded(PlayInfo*)));
        QObject::connect(info,SIGNAL(errored(PlayInfo*)),this,SLOT(playErrored(PlayInfo*)));
        info->load(this->network_manager);
    }
}

void PlayList::parseList(QByteArray &data){
    this->playing=NULL;
    this->removeList();
    bool succed;
    QVariantMap json=QtJson::parse(QString(data),succed).toMap();
    if(succed){
        foreach (QVariant song_obj, json["songs"].toList()) {
            QVariantMap song=song_obj.toMap();
            PlayInfo* info=new PlayInfo(
            song["id"].toInt(),
            song["name"].toString(),
            song["artistName"].toString(),
            song["artistId"].toInt(),
            song["src"].toString(),
            song["duration"].toInt(),
            song["albumSrc"].toString(),
            song["albumName"].toString(),
            song["albumId"].toInt(),
            song["lyric"].toString(),
            song["fav"].toBool());
            this->play_list.append(info);
        }
    }
}

void PlayList::removeList(){
    while(!this->play_list.empty()){
        PlayInfo* play_info=this->play_list.first();
        delete play_info;
        this->play_list.removeFirst();
    }
}

PlayInfo* PlayList::getPlayingMusic(){
    return this->playing;
}

FMInfo* PlayList::getPlayingFM(){
    return this->playing_fm;
}

void PlayList::playLoaded(PlayInfo *info){
    if(this->playing==NULL){
        this->playing=info;
        emit this->loaded();
    }
}

void PlayList::playErrored(PlayInfo *info){
    this->play_list.removeOne(info);
    delete info;
    if(this->play_list.count()<=1){
        this->loadNextList();
    }
}

