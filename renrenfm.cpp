#include "renrenfm.h"
#include <QDir>
#include <QFileInfo>
#include <QListIterator>
#include "resource/rresourcecache.h"

RenrenFm::RenrenFm()
{
    this->player=NULL;
    this->window=NULL;
}

RenrenFm::~RenrenFm(){
    if(this->window!=NULL) delete this->window;
    if(this->player!=NULL) delete this->player;
}

void RenrenFm::init(){
    this->player=new FMPlayer(this);
    this->window=new Window();
}

void RenrenFm::load(){
    this->player->load();
}

void RenrenFm::show(){
    this->window->show();
}

void RenrenFm::LoadStaticResource(){
    this->loadStaticImages();
}

void RenrenFm::loadStaticImages(){
    QDir images("images\\");
    if(!images.exists()) return;
    images.setFilter(QDir::Dirs|QDir::Files);
    QListIterator<QFileInfo> iterator(images.entryInfoList());
    while(iterator.hasNext()){
        QFileInfo fi=iterator.next();
        if(fi.isFile() && fi.suffix().toLower()=="png"){
            RResourceCache::loadImage(fi.baseName()+"_image",fi.filePath());
        }
    }
}

Window* RenrenFm::getWindow(){
    return this->window;
}
