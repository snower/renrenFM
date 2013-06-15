#include "rlistview.h"
#include <QLinkedListIterator>
#include <QWheelEvent>
#include "rslipfence.h"
#include "../player/fminfo.h"
#include "../resource/rresourcecache.h"

RListView::RListView(QWidget *parent) :
    QWidget(parent)
{
    this->init();
}

RListView::~RListView(){
    delete this->item_viewes;
    delete this->item_size;
}

void RListView::init(){
    this->item_viewes=new QLinkedList<RItemView*>();
    this->item_size=new QSize(166,102);
    this->scroll_pos=0;
    this->view_width=0;
    this->view_height=0;

    QObject::connect(((RSlipFence*)this->parentWidget()->parentWidget())->getFence(),SIGNAL(slipStop(bool)),this,SLOT(centerListDetail(bool)));
}
void RListView::resizeEvent(QResizeEvent *event){
    this->scroll_pos=0;
    this->adaptItemView();
    event->accept();
}

void RListView::wheelEvent(QWheelEvent *event){
    int step=event->delta();
    if(this->view_height>this->height() && this->scroll_pos>=this->height()-this->view_height && this->scroll_pos<=0){
        if(-(this->scroll_pos+step)>=this->view_height-this->height()){
            this->scroll_pos=this->height()-this->view_height;
        }
        else if(this->scroll_pos+step>0){
            this->scroll_pos=0;
        }
        else{
            this->scroll_pos+=step;
        }
    }
    int center_offset=(this->width()-((int)this->width()/this->item_size->width())*this->item_size->width())/2;
    this->adaptItemView(center_offset,this->scroll_pos);
    event->accept();
}

void RListView::adaptItemView(int ox,int oy){
    int i=0,j=0;
    QLinkedListIterator<RItemView*> iterator(*this->item_viewes);
    while(iterator.hasNext()){
        RItemView* iv=iterator.next();
        iv->setGeometry(i+ox,j+oy,this->item_size->width(),this->item_size->height());
        i+=this->item_size->width();
        if(i+this->item_size->width()>this->width()){
            i=0;
            j+=this->item_size->height();
        }
    }
    this->view_width=i;
    this->view_height=j;
}

void RListView::addItemView(RItemView* iv){
    this->item_viewes->append(iv);
    iv->setGeometry(0,0,this->item_size->width(),this->item_size->height());
}

void RListView::centerListDetail(bool pos){
    if(!pos){
        int center_offset=(this->width()-((int)this->width()/this->item_size->width())*this->item_size->width())/2;
        this->adaptItemView(center_offset,0);
    }
}

void RListView::addItem(FMInfo *info){
    QImage* cover=RResourceCache::loadImage(info->pic_name,"cache\\"+info->pic_name);
    RItemView* view=new RItemView(cover,info->name,this);
    QObject::connect(view,SIGNAL(clicked()),info,SLOT(play()));
    QObject::connect(info,SIGNAL(statusChanged(bool)),view,SLOT(updateStatus(bool)),Qt::QueuedConnection);
    this->addItemView(view);
    this->adaptItemView();
    view->show();
}
