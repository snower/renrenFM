#include "rresourcecache.h"
#include <QMapIterator>

QMap<QString,RResource*> RResourceCache::resources=QMap<QString,RResource*>();
QImage RResourceCache::default_image=QImage(20,30,QImage::Format_ARGB32);

RResourceCache::RResourceCache()
{
}

QImage* RResourceCache::loadImage(QString name){
    if(resources.contains(name)){
        resources[name]->increaseRefCount();
        return (QImage*)resources[name]->getResource();
    }
    return &default_image;
}

QImage* RResourceCache::loadImage(QString name, QString file_name){
    if(resources.contains(name)){
        resources[name]->increaseRefCount();
        return (QImage*)resources[name]->getResource();
    }
    QImage* img=new QImage();
    img->load(file_name);
    if(!img->isNull()){
        resources[name]=new RResource(name,file_name,img);
        resources[name]->increaseRefCount();
        return img;
    }
    return &default_image;
}

bool RResourceCache::releaseImage(QImage* img){
    QMapIterator<QString,RResource*> iterator(resources);
    RResource* source=NULL;
    while(iterator.hasNext()){
        iterator.next();
        if(iterator.value()->getResource()==img){
            source=iterator.value();
            break;
        }
    }
    if(source!=NULL){
        source->decreaseRefCount();
        if(source->getRefCount()<=0){
            resources.remove(source->getName());
            delete source;
        }
    }
    return true;
}

bool RResourceCache::releaseImage(QString name){
    RResource* source=NULL;
    if(!resources.contains(name)){
        return false;
    }
    source=resources[name];
    if(source!=NULL){
        source->decreaseRefCount();
        if(source->getRefCount()<=0){
            resources.remove(source->getName());
            delete source;
        }
    }
    return true;
}
