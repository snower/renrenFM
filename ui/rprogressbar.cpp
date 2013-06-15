#include "rprogressbar.h"
#include <QPaintEvent>
#include <QMouseEvent>
#include <QCursor>

RProgressBar::RProgressBar(QWidget *parent) :
    QWidget(parent)
{
    this->init();
}

RProgressBar::~RProgressBar(){

}

void RProgressBar::init(){
    this->max_value=100;
    this->step_value=1;
    this->max_color=QColor(204,204,204);
    this->current_values=QList<double>();
    this->current_colores=QList<QColor>();
    this->progress_count=0;
    this->setClicked(false);
}

void RProgressBar::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    this->painterBackGround(&painter);
    this->painterProgress(&painter);
    event->accept();
}

void RProgressBar::painterBackGround(QPainter *painter){
     painter->fillRect(0,0,this->width(),this->height(),this->max_color);
}

void RProgressBar::mouseReleaseEvent(QMouseEvent *event){
    if(this->enable_click){
        double current=(float)event->x()/(float)this->width()*this->max_value;
        this->clicked(current,this->max_value);
        this->current_values[this->progress_count-1]=current;
        this->repaint();
    }
    event->accept();
}

void RProgressBar::painterProgress(QPainter *painter){
    if(this->max_value!=0){
        for(int i=0;i<this->progress_count;i++){
            painter->fillRect(0,0,(double)this->current_values[i]/(double)this->max_value*(float)this->width(),this->height(),this->current_colores[i]);
        }
    }
}

void RProgressBar::addProgress(double current, QColor color){
    this->current_values.append(current);
    this->current_colores.append(color);
    this->progress_count++;
    this->repaint();
}

void RProgressBar::setMaxValue(double value){
    this->max_value=value;
    this->repaint();
}

void RProgressBar::setStepValue(float value){
    this->step_value=value;
    this->repaint();
}

void RProgressBar::updateCurrentValue(int index,double value){
    this->current_values[index]=value;
    this->repaint();
}

void RProgressBar::increaseStep(int index){
    this->current_values[index]+=this->step_value;
    this->repaint();
}

void RProgressBar::decreaseStep(int index){
    this->current_values[index]+=this->step_value;
    this->repaint();
}

void RProgressBar::setClicked(bool is){
    this->enable_click=is;
    if(this->enable_click){
        this->setCursor(QCursor(Qt::PointingHandCursor));
    }
    else{
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}
