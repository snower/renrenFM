#include "rcdplayer.h"
#include <qmath.h>
#include <QPaintEvent>
#include <QResizeEvent>
#include "../resource/rresourcecache.h"

RCdPlayer::RCdPlayer(QWidget *parent) :
    QWidget(parent)
{
    this->init();
}

RCdPlayer::~RCdPlayer(){

}

void RCdPlayer::init(){
    this->cd_img=RResourceCache::loadImage("cd_cover_image");
    this->cover_img=NULL;
    this->play_img=RResourceCache::loadImage("play_big_image");
    this->pause_img=RResourceCache::loadImage("pause_big_image");
    this->timer=new QTimer();
    this->status=true;
    this->is_hover=false;
    this->cover_rotate=0;

    QObject::connect(this->timer,SIGNAL(timeout()),this,SLOT(timeOut()));
    this->setCursor(QCursor(Qt::PointingHandCursor));
    this->setMouseTracking(true);
}

void RCdPlayer::painterCoverImage(QPainter *painter){
    painter->translate(this->width()/2,this->height()/2);
    painter->rotate(this->cover_rotate);
    painter->drawImage(-113,-112,this->cover,0,0,226,226);
    painter->rotate(-this->cover_rotate);
    painter->translate(-this->width()/2,-this->height()/2);
}

void RCdPlayer::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPainterPath path;
    path.addEllipse(this->width()/2-113,this->height()/2-114,226,226);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawImage(0,0,*this->cd_img);
    painter.setClipPath(path);
    if(this->cover_img!=NULL) this->painterCoverImage(&painter);
    if(this->is_hover){
        painter.setBrush(QColor(150,150,150,150));
        painter.drawRect(0,0,this->width(),this->height());
        if(this->status){
            painter.drawImage((this->width()-this->play_img->width())/2,(this->height()-this->play_img->height())/2,*this->play_img);
        }
        else{
            painter.drawImage((this->width()-this->pause_img->width())/2,(this->height()-this->pause_img->height())/2,*this->pause_img);
        }
    }
    event->accept();
}

void RCdPlayer::mouseMoveEvent(QMouseEvent *event){
    int x=event->x()-this->width()/2;
    int y=event->y()-this->height()/2;
    if(pow(x,2)+pow(y,2)<=pow(113,2)){
        if(!this->is_hover){
            this->is_hover=true;
            this->repaint();
        }
    }
    else{
        if(this->is_hover){
            this->is_hover=false;
            this->repaint();
        }
    }
    event->accept();
}

void RCdPlayer::mouseReleaseEvent(QMouseEvent *event){
    int x=event->x()-this->width()/2;
    int y=event->y()-this->height()/2;
    if(pow(x,2)+pow(y,2)<=pow(113,2)){
        emit this->clicked(!this->status);
    }
    event->accept();
}

void RCdPlayer::timeOut(){
    this->cover_rotate+=4;
    if(this->cover_rotate>=360){
        this->cover_rotate=0;
    }
    this->repaint();
}

void RCdPlayer::changeTimer(){
    if(this->status){
        if(!this->timer->isActive()){
            this->timer->start(50);
        }
    }
    else{
        if(this->timer->isActive()){
            this->timer->stop();
        }
    }
}

QImage* RCdPlayer::setCoverImage(QImage *img){
    QImage* old_img=this->cover_img;
    this->cover_img=img;
    this->cover=this->cover_img->scaled(226,226);
    this->changeTimer();
    return old_img;
}

void RCdPlayer::updateStatus(bool status){
    this->status=status;
    this->repaint();
    this->changeTimer();
}
