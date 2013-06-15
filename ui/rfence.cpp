#include "rfence.h"
#include <QResizeEvent>
#include "../resource/rresourcecache.h"

RFence::RFence(QWidget *parent)
	: QWidget(parent)
{
	this->init();
}

RFence::~RFence()
{
	delete this->left_button;
	delete this->right_button;
}

void RFence::setMinValue(int value){
	this->min_value=value;
    if(this->status){
        this->position=this->min_value;
    }
}

void RFence::setMaxValue(int value){
	this->max_value=value;
    if(!this->status){
        this->position=this->max_value;
    }
}

void RFence::init(){
	this->status=true;
	this->left_button=new RButton(this);
	this->right_button=new RButton(this);
	this->timer=new QTimer();
    this->min_value=0;
    this->max_value=30;
    this->position=0;

	this->left_button->setGeometry(0,0,this->width(),this->height());
	this->right_button->setGeometry(0,0,this->width(),this->height());

    RButtonStatusConfig* config=new RButtonStatusConfig(RButton_Status_Default,RResourceCache::loadImage("fence_left_image"));
    config->setIconRect(new QRect(0,100,0,0));
	this->left_button->setStatusConfig(config);
    config=new RButtonStatusConfig(RButton_Status_Hover,RResourceCache::loadImage("fence_left_hover_image"));
    config->setIconRect(new QRect(0,100,0,0));
	this->left_button->setStatusConfig(config);
    config=new RButtonStatusConfig(RButton_Status_Default,RResourceCache::loadImage("fence_right_image"));
    config->setIconRect(new QRect(0,100,0,0));
	this->right_button->setStatusConfig(config);
    config=new RButtonStatusConfig(RButton_Status_Hover,RResourceCache::loadImage("fence_right_hover_image"));
    config->setIconRect(new QRect(0,100,0,0));
	this->right_button->setStatusConfig(config);

    QObject::connect(this->left_button,SIGNAL(clicked(RButton*)),this,SLOT(buttonToggled(RButton*)));
    QObject::connect(this->right_button,SIGNAL(clicked(RButton*)),this,SLOT(buttonToggled(RButton*)));
    QObject::connect(this->timer,SIGNAL(timeout()),this,SLOT(timeOut()));

	this->right_button->hide();
}

void RFence::resizeEvent(QResizeEvent* event){
	this->left_button->setGeometry(0,0,this->width(),this->height());
	this->right_button->setGeometry(0,0,this->width(),this->height());
    event->accept();
}


void RFence::timeOut(){
    int speed=(this->max_value-this->min_value)/10;
    int pos=this->status ? this->x()+speed : this->x()-speed;
    this->position=pos<=this->min_value ? this->min_value : pos>=this->max_value ? this->max_value : pos;
    this->setGeometry(this->position,0,this->width(),this->height());
    this->positionChanged(this->position);
    if(this->position<=this->min_value || this->position>=this->max_value){
		this->timer->stop();
        this->status=this->status ? false : true;
        this->slipStop(this->status);
        return;
	}
}

void RFence::buttonToggled(RButton* button){
	if(this->status){
		this->left_button->hide();
		this->right_button->show();
	}
	else{
		this->right_button->hide();
		this->left_button->show();
	}
    this->left_button->setStatus(RButton_Status_Default);
    this->right_button->setStatus(RButton_Status_Default);
    this->slipStart(this->status);
    this->timer->start(40);
}

int RFence::getPosition(){
    return this->position;
}
