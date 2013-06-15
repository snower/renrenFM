#ifndef RCDPLAYER_H
#define RCDPLAYER_H

#include <QWidget>
#include <QImage>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QBitmap>

class RCdPlayer : public QWidget
{
    Q_OBJECT

private:
    void init();
    void painterCoverImage(QPainter* painter);
    void changeTimer();

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);

public:
    explicit RCdPlayer(QWidget *parent = 0);
    ~RCdPlayer();

private:
    QImage* cd_img;
    QImage* cover_img;
    QImage cover;
    QImage* play_img;
    QImage* pause_img;
    QTimer* timer;
    bool status;
    bool is_hover;
    int cover_rotate;
    
signals:
    void clicked(bool status);
    
public slots:
    void timeOut();
    QImage* setCoverImage(QImage* img);
    void updateStatus(bool status);
};

#endif // RCDPLAYER_H
