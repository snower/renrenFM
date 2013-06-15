#ifndef RVOLUME_H
#define RVOLUME_H

#include <QWidget>
#include "rbutton.h"
#include "rprogressbar.h"

class RVolume : public QWidget
{
    Q_OBJECT
private:
    void init();

protected:
    virtual void resizeEvent(QResizeEvent *);
    virtual void leaveEvent(QEvent *);

public:
    explicit RVolume(QWidget *parent = 0);
    ~RVolume();

private:
    RButton* button;
    RProgressBar *volume;
    
signals:
    void changed(int voiume);
    
public slots:
    void updateVolume(int volume);

private slots:
    void hoverButton(RButton* button,bool hover);
    void change(double volume,double max);
};

#endif // RVOLUME_H
