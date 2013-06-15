#ifndef RRESOURCECACHE_H
#define RRESOURCECACHE_H

#include <QMap>
#include <QImage>
#include "rresource.h"

class RResourceCache
{
private:
    RResourceCache();

public:
    static QImage* loadImage(QString name);
    static QImage* loadImage(QString name,QString file_name);
    static bool releaseImage(QImage* img);
    static bool releaseImage(QString name);

public:
    static QMap<QString,RResource*> resources;
    static QImage default_image;
};

#endif // RRESOURCECACHE_H
