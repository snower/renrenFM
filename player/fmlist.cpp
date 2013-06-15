#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QRegExp>
#include <QStringList>
#include <QLinkedListIterator>
#include "fmlist.h"
#include "../ui/rlistview.h"

FMList::FMList(QNetworkAccessManager* network_manager,RListView* view) : QObject()
{
    this->network_manager=network_manager;
    this->view=view;
    this->init();
}

FMList::~FMList(){
    while(!this->fm_list.empty()){
        FMInfo* info=this->fm_list.first();
        this->fm_list.removeFirst();
        delete info;
    }
}

void FMList::init(){
    this->loaded_count=0;
    this->request=QNetworkRequest(QUrl("http://fm.renren.com/fm/home"));
    QObject::connect(this,SIGNAL(addFM(FMInfo*)),this->view,SLOT(addItem(FMInfo*)),Qt::QueuedConnection);
}

void FMList::load(){
    this->reply=this->network_manager->get(this->request);
    QObject::connect(this->reply,SIGNAL(finished()),this,SLOT(finish()));
}

void FMList::finish(){
    this->html_string=QString(this->reply->readAll());
    this->parse();
    this->loadFM();
    this->reply->deleteLater();
}

void FMList::parse(){
    QRegExp rx("<ul class=\"gallery clearfix\">(.*)</ul>");
    rx.setMinimal(true);
    QString str;

    if(rx.indexIn(this->html_string, 0)>0){
        str=rx.cap(1);
    }
    rx.setPattern("<li.*<img src=\"(.+)\" class=\"pic\"/>.*<h3><a id=\"gallink_(.+)\" href=\"javascript:;\">(.+)</a>.*</li>");
    int pos = 0;
    while((pos = rx.indexIn(str, pos)) != -1){
        this->fm_list.append(new FMInfo(rx.cap(3),rx.cap(2),rx.cap(1)));
        pos += rx.matchedLength();
    }
}

void FMList::loadFM(){
    QLinkedListIterator<FMInfo*> iterator(this->fm_list);
    while(iterator.hasNext()){
        FMInfo* info=iterator.next();
        QObject::connect(info,SIGNAL(loaded(FMInfo*)),this,SLOT(FMLoaded(FMInfo*)));
        QObject::connect(info,SIGNAL(played(FMInfo*)),this,SLOT(FMPlay(FMInfo*)));
        info->load(this->network_manager);
    }
}

void FMList::FMLoaded(FMInfo *info){
    emit this->addFM(info);
    this->loaded_count++;
    if(this->loaded_count>=this->fm_list.count()){
        emit this->FMListLoaded();
    }
}

void FMList::FMPlay(FMInfo *info){
    emit this->played(info);
}

FMInfo* FMList::getFM(int index){
    if(this->fm_list.count()>index){
        return this->fm_list.first();
    }
    return NULL;
}
