#include "rbuttonstatusconfig.h"
#include <QCursor>

RButtonStatusConfig::RButtonStatusConfig(RButton_Status status){
    this->status=status;
    this->text=NULL;
    this->icon=NULL;
    this->init();
}

RButtonStatusConfig::RButtonStatusConfig(RButton_Status status,QString* text){
    this->status=status;
    this->text=text;
    this->icon=NULL;
    this->init();
}

RButtonStatusConfig::RButtonStatusConfig(RButton_Status status,QImage* icon){
    this->status=status;
    this->text=NULL;
    this->icon=icon;
    this->init();
}

RButtonStatusConfig::RButtonStatusConfig(RButton_Status status,QString* text,QImage* icon){
    this->status=status;
    this->text=text;
    this->icon=icon;
    this->init();
}

RButtonStatusConfig::~RButtonStatusConfig(){
    if(this->text_rect!=NULL) delete this->text_rect;
    if(this->icon_rect!=NULL) delete this->icon_rect;
    if(this->cursor!=NULL) delete this->cursor;
}

void RButtonStatusConfig::init(){
    this->text_rect= this->text==NULL ? NULL : new QRect(0,0,0,0);
    this->icon_rect= this->icon==NULL ? NULL : new QRect(0,0,0,0);
    if(this->status==RButton_Status_Disable){
        this->cursor=new QCursor(Qt::ArrowCursor);
    }
    else{
        this->cursor=new QCursor(Qt::PointingHandCursor);
    }
}

RButton_Status RButtonStatusConfig::getStatus(){
    return this->status;
}

void RButtonStatusConfig::setStatus(RButton_Status status){
    this->status=status;
}

QString* RButtonStatusConfig::getText(){
    return this->text;
}

void RButtonStatusConfig::setText(QString* text){
    if(this->text!=NULL) delete this->text;
    this->text=text;
}

QRect* RButtonStatusConfig::getTextRect(){
    return this->text_rect;
}

void RButtonStatusConfig::setTextRect(QRect* rect){
    if(this->text_rect!=NULL) delete this->text_rect;
    this->text_rect=rect;
}

QImage* RButtonStatusConfig::getIcon(){
    return this->icon;
}

void RButtonStatusConfig::setIcon(QImage* icon){
    if(this->icon!=NULL) delete this->icon;
	this->icon=icon;
}

QRect* RButtonStatusConfig::getIconRect(){
    return this->icon_rect;
}

void RButtonStatusConfig::setIconRect(QRect* rect){
    if(this->icon_rect) delete this->icon_rect;
    this->icon_rect=rect;
}

QCursor* RButtonStatusConfig::getCursor(){
    return this->cursor;
}

void RButtonStatusConfig::setCursor(QCursor* cursor){
    if(this->cursor!=NULL) delete this->cursor;
    this->cursor=cursor;
}
