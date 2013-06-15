#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "rslipfence.h"
#include "rview.h"
#include "rplayer.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

private:
    void init();
    
public:
    explicit Window(QWidget *parent = 0);
    ~Window();

    RView* getView();
    RPlayer* getPlayerView();
    
private:
    Ui::Window *ui;
	RSlipFence* slip_fence;
    RView* view;
    RPlayer* player;
};

#endif // WINDOW_H
