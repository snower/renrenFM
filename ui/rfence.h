#ifndef RFENCE_H
#define RFENCE_H

#include <QWidget>
#include <qtimer.h>
#include "rbutton.h"

class RFence : public QWidget
{
	Q_OBJECT
private:
	void init();

public:
	RFence(QWidget *parent);
	~RFence();

	void setMinValue(int value);
	void setMaxValue(int value);
    int getPosition();

protected:
	virtual void resizeEvent(QResizeEvent* event);

private:
	bool status;
	RButton* left_button;
	RButton* right_button;
	QTimer* timer;
	int min_value;
	int max_value;
    int position;

signals:
    void slipStart(bool pos);
    void positionChanged(int pos);
    void slipStop(bool pos);

private slots:
	void timeOut();
	void buttonToggled(RButton* button);
};

#endif // RFENCE_H
