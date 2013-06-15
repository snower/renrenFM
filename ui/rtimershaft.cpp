#include "rtimershaft.h"
#include <QPaintEvent>
#include <QResizeEvent>
#include <QPainter>
#include "../resource/rresourcecache.h"

RTimerShaft::RTimerShaft(QWidget *parent) :
    QWidget(parent)
{
    this->init();
}

RTimerShaft::~RTimerShaft(){
    delete this->label_time;
    delete this->progress_bar;
}

void RTimerShaft::init(){
    this->bg_img=RResourceCache::loadImage("view_bg_image");
    this->label_time=new QLabel(this);
    this->progress_bar=new RProgressBar(this);

    this->label_time->setText("00:00/00:00");
    this->label_time->setStyleSheet("font-size:11px;color:#666666;");
    this->label_time->setAlignment(Qt::AlignCenter);

    this->progress_bar->addProgress(0,QColor(150,150,150));
    this->progress_bar->addProgress(0,QColor(100,100,100));

    QObject::connect(this->progress_bar,SIGNAL(clicked(double,double)),this,SLOT(change(double,double)));
}

void RTimerShaft::paintEvent(QPaintEvent *){
    QPainter painter(this);
    for(int i=0,w=this->bg_img->width(),c=this->width()/w+1;i<c;i++){
        painter.drawImage(i*w,0,*this->bg_img);
    }
}

void RTimerShaft::resizeEvent(QResizeEvent *event){
    this->label_time->setGeometry(this->width()-80,0,80,this->height());
    this->progress_bar->setGeometry(0,this->height()*0.8/2,this->width()-80,this->height()*0.2);
    event->accept();
}

void RTimerShaft::updateDurationStatus(int duration, int duration_long){
    this->progress_bar->updateCurrentValue(0,(float)duration/(float)duration_long*100);
    this->label_time->setText(this->formatDuration(duration)+"/"+this->formatDuration(duration_long));
}

void RTimerShaft::updateBufferStatus(int percentFilled){
    this->progress_bar->updateCurrentValue(1,percentFilled);
}

QString RTimerShaft::formatDuration(int duration){
    QString m=QString::number((int)duration/60);
    QString s=QString::number((int)duration%60);
    m= m.length()== 1 ? "0" + m : m;
    s= s.length()== 1 ? "0" + s : s;
    return m+":"+s;
}

void RTimerShaft::change(double duration, double max){
    emit this->changed(duration);
}
