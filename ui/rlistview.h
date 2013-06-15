#ifndef RLISTVIEW_H
#define RLISTVIEW_H

#include <QWidget>
#include <QLinkedList>
#include <QSize>
#include "ritemview.h"

class FMInfo;

class RListView : public QWidget
{
    Q_OBJECT

private:
    void init();
    void adaptItemView(int ox=0,int oy=0);

protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void wheelEvent(QWheelEvent *);

public:
    explicit RListView(QWidget *parent = 0);
    ~RListView();

    void addItemView(RItemView* iv);

private:
    QLinkedList<RItemView*>* item_viewes;
    QSize* item_size;
    int scroll_pos;
    int view_width;
    int view_height;
    
signals:
    
public slots:
    void centerListDetail(bool pos);
    void addItem(FMInfo *info);
};

#endif // RLISTVIEW_H
