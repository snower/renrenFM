#ifndef RITEMVIEW_H
#define RITEMVIEW_H

#include <QWidget>
#include <QImage>
#include <QString>

class RItemView : public QWidget
{
    Q_OBJECT

private:
    void painterCover(QPainter* painter);
    void painterTitle(QPainter* painter);

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void leaveEvent(QEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);

public:
    explicit RItemView(QImage* cover,QString title,QWidget *parent = 0);

private:
    QImage* cover;
    QString title;
    QImage* hover_img;
    int c_margin;
    int ct_margin;
    bool is_hover;
    bool status;
    
signals:
    void clicked();
public slots:
    void updateStatus(bool status);
};

#endif // RITEMVIEW_H
