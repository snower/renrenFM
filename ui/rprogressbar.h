#ifndef RPROGRESSBAR_H
#define RPROGRESSBAR_H

#include <QWidget>
#include <QList>
#include <QPainter>

class RProgressBar : public QWidget
{
    Q_OBJECT

private:
    void init();
    void painterBackGround(QPainter* painter);
    void painterProgress(QPainter *painter);

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);

public:
    explicit RProgressBar(QWidget *parent = 0);
    ~RProgressBar();

    void addProgress(double current, QColor color);

private:
    double max_value;
    float step_value;
    QColor max_color;
    QList<double> current_values;
    QList<QColor> current_colores;
    int progress_count;
    bool enable_click;
    
signals:
    void clicked(double current,double max);
    
public slots:
    void setMaxValue(double value);
    void setStepValue(float value);
    void updateCurrentValue(int index,double value);
    void increaseStep(int index);
    void decreaseStep(int index);
    void setClicked(bool is);
};

#endif // RPROGRESSBAR_H
