#ifndef RBUTTONSTATUSCONFIG_H
#define RBUTTONSTATUSCONFIG_H

#include <QString>
#include <QImage>
#include <QRect>

#define RBUTTON_STATUS_COUNT 4

enum RButton_Status{
    RButton_Status_Default=0,
    RButton_Status_Hover=1,
    RButton_Status_Active=2,
	RButton_Status_Disable=3
};

class RButtonStatusConfig{
private:
    void init();
public:
    RButtonStatusConfig(RButton_Status status);
    RButtonStatusConfig(RButton_Status status,QString* text);
    RButtonStatusConfig(RButton_Status status,QImage* icon);
    RButtonStatusConfig(RButton_Status status,QString* text,QImage* icon);
    ~RButtonStatusConfig();

    RButton_Status getStatus();
    void setStatus(RButton_Status status);
    QString* getText();
    void setText(QString* text);
    QRect* getTextRect();
    void setTextRect(QRect* rect);
    QImage* getIcon();
    void setIcon(QImage* icon);
    QRect* getIconRect();
    void setIconRect(QRect* rect);
    QCursor* getCursor();
    void setCursor(QCursor* cursor);

private:
    RButton_Status status;
    QString* text;
    QImage* icon;
    QRect* text_rect;
    QRect* icon_rect;
    QCursor* cursor;
};

#endif // RBUTTONSTATUSCONFIG_H
