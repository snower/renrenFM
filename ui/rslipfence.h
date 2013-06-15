#ifndef RSLIPTAP_H
#define RSLIPTAP_H

#include <QWidget>
#include "rfence.h"

class RSlipFence : public QWidget
{
	Q_OBJECT
private:
	void init();

public:
	RSlipFence(QWidget *parent);
	~RSlipFence();

    void setLeftWidget(QWidget* widget);
    void setRightWidget(QWidget* widget);
    RFence* getFence();

protected:
	virtual void resizeEvent(QResizeEvent* event);

private:
	RFence* fence;
	QWidget* left_widget;
	QWidget* right_widget;
    int fence_width;
    int default_left_size;
    int default_right_size;

private slots:
    void updateSize(int pos);
};

#endif // RSLIPTAP_H
