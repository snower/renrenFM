#include "rslipfence.h"
#include <QResizeEvent>

RSlipFence::RSlipFence(QWidget *parent)
	: QWidget(parent)
{
	this->init();
}

RSlipFence::~RSlipFence()
{
	delete this->fence;
}

void RSlipFence::init(){
    this->left_widget=NULL;
    this->right_widget=NULL;
	this->fence=new RFence(this);
    this->fence_width=35;
    this->default_left_size=170;
    this->default_right_size=100;

    this->fence->setGeometry(this->default_left_size,0,this->fence_width,this->height());
    this->fence->setMinValue(this->default_left_size);
    this->fence->setMaxValue(this->width()-this->default_right_size-this->fence_width);

    QObject::connect(this->fence,SIGNAL(positionChanged(int)),this,SLOT(updateSize(int)));
}

void RSlipFence::resizeEvent(QResizeEvent* event){
    this->fence->setGeometry(this->default_left_size,0,this->fence_width,this->height());
    this->fence->setMaxValue(this->width()-this->default_right_size-this->fence_width);
    if(this->left_widget!=NULL){
        this->left_widget->setGeometry(0,0,this->fence->getPosition(),this->height());
    }
    if(this->right_widget!=NULL){
        this->right_widget->setGeometry(this->fence->getPosition()+this->fence_width,0,this->width()-(this->fence->getPosition()+this->fence_width),this->height());
    }
    event->accept();
}

void RSlipFence::updateSize(int pos){
    if(this->left_widget!=NULL){
        this->left_widget->setGeometry(0,0,pos,this->height());
    }
    if(this->right_widget!=NULL){
        this->right_widget->setGeometry(pos+this->fence_width,0,this->width()-(pos+this->fence_width),this->height());
    }
}

void RSlipFence::setLeftWidget(QWidget *widget){
    if(this->left_widget!=NULL) delete this->left_widget;
    this->left_widget=widget;
}

void RSlipFence::setRightWidget(QWidget *widget){
    if(this->right_widget!=NULL) delete this->right_widget;
    this->right_widget=widget;
}

RFence* RSlipFence::getFence(){
    return this->fence;
}
