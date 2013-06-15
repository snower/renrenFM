#include "ritemview.h"
#include <qmath.h>
#include <QPainter>
#include <QColor>
#include <QBrush>
#include <QPen>
#include <QLinearGradient>
#include <QCursor>
#include <QPaintEvent>
#include <QEvent>
#include <QMouseEvent>
#include <QBitmap>
#include "../resource/rresourcecache.h"

RItemView::RItemView(QImage *cover, QString title, QWidget *parent) :
    QWidget(parent)
{
    this->cover=cover;
    this->title=title;
    this->hover_img=RResourceCache::loadImage("play_image");
    this->c_margin=10;
    this->ct_margin=10;
    this->is_hover=false;
    this->status=false;

    this->setCursor(QCursor(Qt::PointingHandCursor));
    this->setMouseTracking(true);
}

void RItemView::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    this->painterTitle(&painter);
    this->painterCover(&painter);
    event->accept();
}

void RItemView::painterCover(QPainter *painter){
    QPainterPath path;
    path.addRoundedRect(this->c_margin,(this->height()-82)/2,82,82,15,15);
    QLinearGradient gradient(this->c_margin,(this->height()-82)/2, this->c_margin,(this->height()-82)/2+20);
    gradient.setColorAt(0, QColor(153,153,153));
    gradient.setColorAt(1, QColor(153,153,153,0));
    QBrush brush(gradient);
    painter->setClipPath(path);
    painter->drawImage(this->c_margin,(this->height()-82)/2,*this->cover,0,0,82,82);

    painter->setPen(QPen(brush,3.5,Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawRoundRect(this->c_margin,(this->height()-82)/2,82,82,15,15);

    if(this->is_hover || this->status){
        painter->setBrush(QColor(150,150,150,100));
        painter->drawRect(0,0,this->width(),this->height());
        painter->drawImage(this->c_margin+(82-this->hover_img->width())/2,(this->height()-this->hover_img->height())/2,*this->hover_img);
    }
}

void RItemView::painterTitle(QPainter *painter){
    QFont old_font=painter->font();
    painter->setFont(QFont("Tahoma,Verdana,STHeiTi,simsun,sans-serif",9,QFont::Bold));
    painter->drawText(this->c_margin+82+this->ct_margin,0,this->width()-this->c_margin-82-this->ct_margin,this->height(),Qt::AlignVCenter,this->title);
    painter->setFont(old_font);
}

void RItemView::mouseMoveEvent(QMouseEvent *event){
    int x=event->x()-this->c_margin;
    int y=event->y()-(this->height()-82)/2;
    if(x>=0 && y>=0 && x<=82 && y<=82){
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

void RItemView::leaveEvent(QEvent *event){
    this->is_hover=false;
    this->repaint();
    event->accept();
}

void RItemView::mouseReleaseEvent(QMouseEvent *event){
    int x=event->x()-this->c_margin;
    int y=event->y()-(this->height()-82)/2;
    if(x>=0 && y>=0 && x<=82 && y<=82){
        emit this->clicked();
    }
    event->accept();
}

void RItemView::updateStatus(bool status){
    this->status=status;
    this->repaint();
}
