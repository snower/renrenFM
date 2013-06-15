#include "rview.h"
#include <QPainter>
#include <QPaintEvent>
#include <QResizeEvent>
#include "../resource/rresourcecache.h"

RView::RView(QWidget *parent) :
    QWidget(parent)
{
    this->init();
}

RView::~RView(){
}

void RView::init(){
    this->bg_img=RResourceCache::loadImage("view_bg_image");
    this->logo_img=RResourceCache::loadImage("logo_image");
    this->list_view=new RListView(this);
    this->list_view->setGeometry(0,64,this->width(),this->height()-64);
}

void RView::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    this->painterBackGround(&painter);
    this->painterLogo(&painter);
    event->accept();
}

void RView::resizeEvent(QResizeEvent *event){
    this->list_view->setGeometry(0,64,this->width(),this->height()-64);
    event->accept();
}

void RView::painterBackGround(QPainter *painter){
    QBrush brush;
    brush.setTextureImage(*this->bg_img);
    brush.setStyle(Qt::TexturePattern);
    QPen pen(brush,0);
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawRect(0,0,this->width(),this->height());
}

void RView::painterLogo(QPainter *painter){
    painter->drawImage(0,0,*this->logo_img);
}

RListView* RView::getList(){
    return this->list_view;
}
