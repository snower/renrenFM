#ifndef RENRENFM_H
#define RENRENFM_H

#include "ui\window.h"
#include "player/fmplayer.h"

class RenrenFm
{
private:
    void loadStaticImages();

public:
    RenrenFm();
    ~RenrenFm();

    void LoadStaticResource();
    void init();
    void load();
    void show();

    Window* getWindow();

private:
    Window* window;
    FMPlayer* player;
};

#endif // RENRENFM_H
