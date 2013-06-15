#ifndef RTIMERSHAFT_H
#define RTIMERSHAFT_H

#include <QWidget>
#include <QLabel>
#include "rprogressbar.h"

class RTimerShaft : public QWidget
{
    Q_OBJECT
private:
    void init();
    QString formatDuration(int duration);

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent *);

public:
    explicit RTimerShaft(QWidget *parent = 0);
    ~RTimerShaft();

private:
    QImage* bg_img;
    QLabel* label_time;
    RProgressBar* progress_bar;
    
signals:
    void changed(int duration);
    
public slots:
    void updateDurationStatus(int duration, int duration_long);
    void updateBufferStatus(int percentFilled);
    void change(double duration,double max);

};

#endif // RTIMERSHAFT_H
