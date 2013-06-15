#include "rvolume.h"
#include <QResizeEvent>
#include <QEvent>
#include "../resource/rresourcecache.h"

RVolume::RVolume(QWidget *parent) :
    QWidget(parent)
{
    this->init();
}

RVolume::~RVolume(){
    delete this->button;
    delete this->volume;
}

void RVolume::init(){
    this->button=new RButton(this);
    this->volume=new RProgressBar(this);

    RButtonStatusConfig* config=new RButtonStatusConfig(RButton_Status_Default,RResourceCache::loadImage("volume_image"));
    this->button->setStatusConfig(config);
    config=new RButtonStatusConfig(RButton_Status_Hover,RResourceCache::loadImage("volume_hover_image"));
    this->button->setStatusConfig(config);

    this->volume->addProgress(0,QColor(100,100,100));
    this->volume->setClicked(true);

    QObject::connect(this->button,SIGNAL(hovered(RButton*,bool)),this,SLOT(hoverButton(RButton*,bool)));
    QObject::connect(this->volume,SIGNAL(clicked(double,double)),this,SLOT(change(double,double)));
    this->volume->hide();
}

void RVolume::resizeEvent(QResizeEvent *event){
    this->button->setGeometry(0,0,42,42);
    this->volume->setGeometry(52,18,100,5);
    event->accept();
}

void RVolume::leaveEvent(QEvent *event){
    this->volume->hide();
    event->accept();
}

void RVolume::hoverButton(RButton *button, bool hover){
    if(hover){
        this->volume->show();
    }
}

void RVolume::updateVolume(int volume){
    this->volume->updateCurrentValue(0,volume);
}

void RVolume::change(double volume,double max){
    emit this->changed(volume);
}
