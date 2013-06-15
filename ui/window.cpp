#include "window.h"
#include "ui_window.h"
#include "ritemview.h"
#include "../resource/rresourcecache.h"

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window)
{
    Qt::WindowFlags flags = Qt::Window;
    flags |= Qt::CustomizeWindowHint;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    flags |= Qt::MSWindowsFixedSizeDialogHint;
    flags |= Qt::FramelessWindowHint;
    ui->setupUi(this);
    this->init();
    this->setWindowFlags(flags);
}

Window::~Window()
{
    delete ui;
}

void Window::init(){
    this->slip_fence=new RSlipFence(this);
    this->view=new RView(this->slip_fence);
    this->player=new RPlayer(this->slip_fence);

    this->slip_fence->setGeometry(0,0,900,450);
    this->slip_fence->setLeftWidget(this->view);
    this->slip_fence->setRightWidget(this->player);
}

RView* Window::getView(){
    return this->view;
}

RPlayer* Window::getPlayerView(){
    return this->player;
}
