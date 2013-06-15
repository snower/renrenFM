#ifndef RVIEW_H
#define RVIEW_H

#include <QWidget>
#include <QImage>
#include "rlistview.h"

class RView : public QWidget
{
    Q_OBJECT

private:
    void init();
    void painterBackGround(QPainter* painter);
    void painterLogo(QPainter* painter);

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent* event);

public:
    explicit RView(QWidget *parent = 0);
    ~RView();

    RListView* getList();

private:
    QImage* bg_img;
    QImage* logo_img;
    RListView* list_view;
    
signals:
    
public slots:
    
};

#endif // RVIEW_H
