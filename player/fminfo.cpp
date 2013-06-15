#include "fminfo.h"
#include <QFile>
#include <QCryptographicHash>

FMInfo::FMInfo(QString name,QString id,QString pic_url) : QObject()
{
    this->name=name;
    this->id=id;
    this->pic_url=pic_url;
    this->reply=NULL;
    this->is_loaded=false;
    this->is_playing=false;
    this->getPicName();
}

FMInfo::~FMInfo(){
}

void FMInfo::load(QNetworkAccessManager *network_manager){
    if(QFile::exists("cache\\"+this->pic_url)){
        emit this->loaded(this);
        return;
    }
    this->request=QNetworkRequest(QUrl(this->pic_url));
    this->reply=network_manager->get(this->request);
    QObject::connect(this->reply,SIGNAL(finished()),this,SLOT(loadFinish()));
}

void FMInfo::loadFinish(){
    QByteArray data=this->reply->readAll();
    this->writeToFile(data);
    emit this->loaded(this);
    this->is_loaded=true;
    this->reply->deleteLater();
}

void FMInfo::writeToFile(QByteArray &data){
    QFile file("cache\\"+this->pic_name);
    if (!file.open(QIODevice::WriteOnly)) return;
    file.write(data);
    file.close();
}

void FMInfo::play(){
    emit this->played(this);
}

void FMInfo::getPicName(){
    QCryptographicHash ch(QCryptographicHash::Md5);
    QByteArray pic_url_ba;
    pic_url_ba.append(this->pic_url);
    ch.addData(pic_url_ba);
    this->pic_name=QString(ch.result().toHex())+".jpg";
}

void FMInfo::changeStatus(bool status){
    this->is_playing=status;
    emit statusChanged(this->is_playing);
}
