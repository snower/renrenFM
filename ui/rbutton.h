#ifndef RBUTTON_H
#define RBUTTON_H

#include <QWidget>
#include "rbuttonstatusconfig.h"

class RButton : public QWidget
{ 
    Q_OBJECT
private:
    void init();

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);

public:
    RButton(QWidget *parent=NULL);
    ~RButton();

    void setStatusConfig(RButtonStatusConfig* config);
	void setStatus(RButton_Status status);

signals:
    void clicked(RButton* button);
    void hovered(RButton* button,bool hover);

private:
    RButtonStatusConfig* config_statuses[RBUTTON_STATUS_COUNT];
    RButton_Status status;
};

#endif // RBUTTON_H
