#include "rbutton.h"
#include <QPainter>
#include <QCursor>
#include <QPaintEvent>
#include <QEvent>
#include <QMouseEvent>


RButton::RButton(QWidget *parent):QWidget(parent)
{
    this->init();
}

RButton::~RButton(){
    for(int i=0;i<RBUTTON_STATUS_COUNT;i++){
		if(this->config_statuses[i]!=NULL){
			delete this->config_statuses[i];
		}
	}
}

void RButton::init(){
    this->status=RButton_Status_Default;
    for(int i=0;i<RBUTTON_STATUS_COUNT;i++){
		this->config_statuses[i]=NULL;
	}
}

void RButton::paintEvent(QPaintEvent *event){
    QPainter painter(this);
	RButtonStatusConfig* config=NULL;
	for(int i=this->status;i>=0 && config==NULL;i--){
		config=this->config_statuses[i];
	}
	if(config!=NULL){
        if(config->getText()!=NULL){
            painter.drawText(0,0,*config->getText());
        }
        if(config->getIcon()!=NULL){
            QRect* icon_rect=config->getIconRect();
			painter.drawImage(0,0,*config->getIcon(),icon_rect->x(),icon_rect->y(),icon_rect->width()<=0 ? this->width() : icon_rect->width(),icon_rect->height()<=0 ? this->height() : icon_rect->height());
        }
    }
    this->setCursor(*config->getCursor());
    event->accept();
}

void RButton::enterEvent(QEvent *event){
    if(this->status==RButton_Status_Disable) return;
    this->status=RButton_Status_Hover;
    emit this->hovered(this,true);
    this->repaint();
    event->accept();
}

void RButton::leaveEvent(QEvent *event){
    if(this->status==RButton_Status_Disable) return;
    this->status=RButton_Status_Default;
    emit this->hovered(this,false);
    this->repaint();
    event->accept();
}

void RButton::mousePressEvent(QMouseEvent *event){
    if(this->status==RButton_Status_Disable) return;
    this->status=RButton_Status_Active;
    this->repaint();
    event->accept();
}

void RButton::mouseReleaseEvent(QMouseEvent *event){
    if(this->status==RButton_Status_Disable) return;
    emit this->clicked(this);
    this->status=RButton_Status_Hover;
    this->repaint();
    event->accept();
}

void RButton::setStatusConfig(RButtonStatusConfig *config){
	if(this->config_statuses[config->getStatus()]!=NULL) delete this->config_statuses[config->getStatus()];
	this->config_statuses[config->getStatus()]=config;
}

void RButton::setStatus(RButton_Status status){
	this->status=status;
    this->repaint();
}
