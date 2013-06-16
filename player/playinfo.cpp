#include "playinfo.h"
#include <QCryptographicHash>
#include <QFile>
#include <QLinkedListIterator>

PlayInfo::PlayInfo(int id,QString name,QString artistName,int artistId,QString src,int duration,QString albumSrc,QString albumName,int albumId,QString lyric,bool fav) : QObject()
{
    this->id=id;
    this->name=name;
    this->artistName=artistName;
    this->artistId=artistId;
    this->src=src;
    this->duration=duration;
    this->albumSrc=albumSrc;
    this->albumName=albumName;
    this->albumId=albumId;
    this->lyric=lyric;
    this->fav=fav;
    this->src_name=this->getName(this->src,"mp3");
    this->albumSrc_name=this->getName(this->albumSrc,"jpg");

    this->init();
}

PlayInfo::~PlayInfo(){

}

void PlayInfo::init(){
    this->music_loaded=false;
    this->album_loaded=false;
    this->error=false;
    this->load_music_count=0;
    this->load_album_count=0;

    this->music_request=QNetworkRequest(QUrl(this->src));
    this->music_request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/27.0.1453.110 Safari/537.36");
    this->music_request.setRawHeader("Cookie","anonymid=hdq1g9ye935msf; _r01_=1; mop_uniq_ckid=218.249.129.163_1363841957_716501246; _de=04E8DB16E8685A4244B0A57815E527E7696BF75400CE19CC; __utma=151146938.1799656108.1369021087.1369021087.1369021087.1; __utmz=151146938.1369021087.1.1.utmcsr=renren.com|utmccn=(referral)|utmcmd=referral|utmcct=/321065350; XNESSESSIONID=9baf8c8cb951; p=431002edaf959a5f65bec9f34f1f45740; ap=321065350; societyguester=9191a5c5b093cf15e0754a6dc4c2edda0; id=321065350; xnsid=c9288a57; loginfrom=null; vip=1");
    this->music_request.setRawHeader("Accept-Encoding","identity;q=1, *;q=0");
    this->music_request.setRawHeader("Referer","http://fm.renren.com/fm/home?from=3&songId=undefined&radioId=undefined");

    this->album_request=QNetworkRequest(QUrl(this->albumSrc));
}

void PlayInfo::loadMusic(){
    if(this->load_music_count>PLAY_RELOAD_COUNT){
        this->error=true;
        emit this->errored(this);
        return;
    }
    if(!QFile::exists("cache\\"+this->src_name)){
        this->music_reply=this->network_manager->get(this->music_request);
        QObject::connect(this->music_reply,SIGNAL(finished()),this,SLOT(musicLoaded()));
    }
    else{
        this->music_loaded=true;
    }
    this->load_music_count++;
}

void PlayInfo::loadAlbum(){
    if(this->load_album_count>PLAY_RELOAD_COUNT){
        this->error=true;
        emit this->errored(this);
        return;
    }
    if(!QFile::exists("cache\\"+this->albumSrc_name)){
        this->album_reply=this->network_manager->get(this->album_request);
        QObject::connect(this->album_reply,SIGNAL(finished()),this,SLOT(albumLoaded()));
    }
    else{
        this->album_loaded=true;
    }
    this->load_album_count++;
}

void PlayInfo::load(QNetworkAccessManager* network_manager){
    this->network_manager=network_manager;
    this->loadMusic();
    this->loadAlbum();
    if(this->music_loaded && this->album_loaded){
        emit this->loaded(this);
    }
}

QString PlayInfo::getName(QString name,QString type){
    QCryptographicHash ch(QCryptographicHash::Md5);
    QByteArray pic_url_ba;
    pic_url_ba.append(name);
    ch.addData(pic_url_ba);
    return QString(ch.result().toHex())+"."+type;
}

void PlayInfo::writeToFile(QString name, QByteArray &data){
    QFile file("cache\\"+name);
    if (!file.open(QIODevice::WriteOnly)) return;
    file.write(data);
    file.close();
}

void PlayInfo::musicLoaded(){
    if(this->music_reply->error()!=QNetworkReply::NoError){
        this->music_reply->deleteLater();
        return;
    }
    QByteArray data=this->music_reply->readAll();
    if(!data.isEmpty()){
        this->writeToFile(this->src_name,data);
        this->music_loaded=true;
        if(this->album_loaded){
            emit this->loaded(this);
        }
        this->music_reply->deleteLater();
    }
    else{
        this->music_reply->deleteLater();
        this->loadMusic();
    }
}

void PlayInfo::albumLoaded(){
    if(this->album_reply->error()!=QNetworkReply::NoError){
        this->album_reply->deleteLater();
        return;
    }
    QByteArray data=this->album_reply->readAll();
    if(!data.isEmpty()){
        this->writeToFile(this->albumSrc_name,data);
        this->album_loaded=true;
        if(this->music_loaded){
            emit this->loaded(this);
        }
        this->album_reply->deleteLater();
    }
    else{
        this->album_reply->deleteLater();
        this->loadAlbum();
    }
}

bool PlayInfo::isLoaded(){
    return this->music_loaded && this->album_loaded;
}

bool PlayInfo::isError(){
    return this->error;
}
