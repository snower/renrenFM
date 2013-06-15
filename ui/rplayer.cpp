#include "rplayer.h"
#include <QFont>
#include <QPalette>
#include <QPaintEvent>
#include <QResizeEvent>
#include "rslipfence.h"
#include "../resource/rresourcecache.h"
#include "../player/playinfo.h"

RPlayer::RPlayer(QWidget *parent) :
    QWidget(parent)
{
    this->init();
}

RPlayer::~RPlayer(){
    delete this->button_love;
    delete this->button_share;
    delete this->button_no;
    delete this->button_next;
}

void RPlayer::init(){
    this->bg_pannel=RResourceCache::loadImage("bg_pannel_image");
    this->bg_radio=RResourceCache::loadImage("radio_bg_image");
    this->cd_player=new RCdPlayer(this);
    this->button_love=new RButton(this);
    this->button_share=new RButton(this);
    this->button_no=new RButton(this);
    this->button_next=new RButton(this);
    this->label_fm_title=new QLabel(this);
    this->label_album=new QLabel(this);
    this->label_title=new QLabel(this);
    this->timer_shaft=new RTimerShaft(this);
    this->volume=new RVolume(this);
    this->status=true;

    this->cd_player->setGeometry(60,30,283,283);
    this->timer_shaft->setGeometry(350,270,320,15);
    this->volume->setGeometry(350,290,152,42);

    this->initButton();
    this->initMusicInfo();
    QObject::connect(((RSlipFence*)this->parentWidget())->getFence(),SIGNAL(slipStart(bool)),this,SLOT(changeToPlayre(bool)));
    QObject::connect(((RSlipFence*)this->parentWidget())->getFence(),SIGNAL(slipStop(bool)),this,SLOT(changeToSideBar(bool)));

    QObject::connect(this->cd_player,SIGNAL(clicked(bool)),this,SLOT(playBtnClicked(bool)));
    QObject::connect(this->button_next,SIGNAL(clicked(RButton*)),this,SLOT(nextBtnClicked()));
    QObject::connect(this->timer_shaft,SIGNAL(changed(int)),this,SLOT(timerShaftClicked(int)));
    QObject::connect(this->volume,SIGNAL(changed(int)),this,SLOT(volumeClicked(int)));
}

void RPlayer::initButton(){
    this->button_love->setGeometry(100,315,150,150);
    this->button_share->setGeometry(235,310,150,150);
    this->button_no->setGeometry(360,315,150,150);
    this->button_next->setGeometry(490,315,150,150);

    RButtonStatusConfig* config=new RButtonStatusConfig(RButton_Status_Default,RResourceCache::loadImage("btn_love_image"));
    this->button_love->setStatusConfig(config);
    config=new RButtonStatusConfig(RButton_Status_Hover,RResourceCache::loadImage("btn_love_hover_image"));
    this->button_love->setStatusConfig(config);
    config=new RButtonStatusConfig(RButton_Status_Active,RResourceCache::loadImage("btn_love_active_image"));
    this->button_love->setStatusConfig(config);
    config=new RButtonStatusConfig(RButton_Status_Disable,RResourceCache::loadImage("btn_love_image"));
    this->button_love->setStatusConfig(config);

    config=new RButtonStatusConfig(RButton_Status_Default,RResourceCache::loadImage("btn_share_image"));
    this->button_share->setStatusConfig(config);
    config=new RButtonStatusConfig(RButton_Status_Hover,RResourceCache::loadImage("btn_share_hover_image"));
    this->button_share->setStatusConfig(config);
    config=new RButtonStatusConfig(RButton_Status_Active,RResourceCache::loadImage("btn_share_active_image"));
    this->button_share->setStatusConfig(config);
    config=new RButtonStatusConfig(RButton_Status_Disable,RResourceCache::loadImage("btn_share_image"));
    this->button_share->setStatusConfig(config);

    config=new RButtonStatusConfig(RButton_Status_Default,RResourceCache::loadImage("btn_no_image"));
    this->button_no->setStatusConfig(config);
    config=new RButtonStatusConfig(RButton_Status_Hover,RResourceCache::loadImage("btn_no_hover_image"));
    this->button_no->setStatusConfig(config);
    config=new RButtonStatusConfig(RButton_Status_Active,RResourceCache::loadImage("btn_no_active_image"));
    this->button_no->setStatusConfig(config);
    config=new RButtonStatusConfig(RButton_Status_Disable,RResourceCache::loadImage("btn_no_image"));
    this->button_no->setStatusConfig(config);

    config=new RButtonStatusConfig(RButton_Status_Default,RResourceCache::loadImage("btn_next_image"));
    this->button_next->setStatusConfig(config);
    config=new RButtonStatusConfig(RButton_Status_Hover,RResourceCache::loadImage("btn_next_hover_image"));
    this->button_next->setStatusConfig(config);
    config=new RButtonStatusConfig(RButton_Status_Active,RResourceCache::loadImage("btn_next_active_image"));
    this->button_next->setStatusConfig(config);
}

void RPlayer::initMusicInfo(){
    this->label_fm_title->setGeometry(370,120,300,50);
    this->label_album->setGeometry(370,180,300,30);
    this->label_title->setGeometry(370,230,300,30);

    this->label_fm_title->setStyleSheet("color:#666666;font-family:\"Microsoft YaHei\";font-size:42px;");
    this->label_album->setStyleSheet("color:#666666;font-family:\"Microsoft YaHei\";font-size:24px;font-weight:400px;");
    this->label_title->setStyleSheet("color:#666666;font-family:\"Microsoft YaHei\";font-size:16px;font-weight:600px;");
}

void RPlayer::painterBackGround(QPainter *painter){
    QBrush brush;
    brush.setTextureImage(*this->bg_pannel);
    brush.setStyle(Qt::TexturePattern);
    QPen pen(brush,0);
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawRect(0,0,this->width(),this->height());
    if(this->status) painter->drawImage(20,20,*this->bg_radio);
}

void RPlayer::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    this->painterBackGround(&painter);
    event->accept();
}

void RPlayer::changeStatus(bool status){
    if(status){
        this->cd_player->show();
        this->button_love->setGeometry(100,315,150,150);
        this->button_share->show();
        this->button_no->setGeometry(360,315,150,150);
        this->button_next->setGeometry(490,315,150,150);
    }
    else{
        this->cd_player->hide();
        this->button_love->setGeometry(-25,0,150,150);
        this->button_share->hide();
        this->button_no->setGeometry(-25,150,150,150);
        this->button_next->setGeometry(-25,300,150,150);
    }
    this->status=status;
}

void RPlayer::changeToSideBar(bool pos){
    if(!pos){
        this->changeStatus(false);
    }
}

void RPlayer::changeToPlayre(bool pos){
    if(!pos){
        this->changeStatus(true);
    }
}

void RPlayer::updatePlayerInfo(PlayInfo *info){
    this->label_fm_title->setText(info->artistName);
    this->label_album->setText(info->albumName);
    this->label_title->setText(info->name);
    QImage* cover=RResourceCache::loadImage(info->albumSrc_name,"cache\\"+info->albumSrc_name);
    RResourceCache::releaseImage(this->cd_player->setCoverImage(cover));
    this->timer_shaft->updateDurationStatus(0,info->duration);
}

void RPlayer::updateBufferStatus(int percentFilled){
    this->timer_shaft->updateBufferStatus(percentFilled);
}

void RPlayer::updateDuration(int duration, int duration_long){
    this->timer_shaft->updateDurationStatus(duration,duration_long);
}

void RPlayer::updateVolume(int volume){
    this->volume->updateVolume(volume);
}

void RPlayer::playBtnClicked(bool status){
    emit this->playStatusChanged(status);
}

void RPlayer::nextBtnClicked(){
    emit this->nexted();
}

void RPlayer::timerShaftClicked(int duration){
    emit this->durationChnanged(duration);
}

void RPlayer::volumeClicked(int volume){
    emit this->volumeChanged(volume);
}

void RPlayer::updatePlayerStatus(int status){
    switch (status) {
    case 0:
        this->cd_player->updateStatus(false);
        break;
    case 1:
        this->cd_player->updateStatus(true);
        break;
    case 2:
        this->cd_player->updateStatus(false);
        break;
    default:
        this->cd_player->updateStatus(false);
        break;
    }
}
