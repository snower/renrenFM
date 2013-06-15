#ifndef RRESOURCE_H
#define RRESOURCE_H

#include <QDateTime>

class RResource
{
public:
    RResource(QString name, QString file_name, void *resource);
    ~RResource();

    QString getName();
    QString getFileName();
    void* getResource();
    int getRefCount();
    bool increaseRefCount();
    bool decreaseRefCount();

private:
    QString name;
    QString file_name;
    void* resource;
    int ref_count;
    QDateTime load_time;
    QDateTime ref_time;
};

#endif // RRESOURCE_H
