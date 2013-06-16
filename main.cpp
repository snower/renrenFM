#include <QApplication>
#include "renrenfm.h"

int main(int argc, char *argv[])
{
    QApplication::addLibraryPath("plugins");
    QApplication a(argc, argv);
    RenrenFm fm;
    fm.LoadStaticResource();
    fm.init();
    fm.load();
    fm.show();
    return a.exec();
}
