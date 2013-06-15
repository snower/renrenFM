#include "rresource.h"

RResource::RResource(QString name,QString file_name,void* resource)
{
    this->name=name;
    this->file_name=file_name;
    this->resource=resource;
    this->ref_count=0;
    this->load_time=QDateTime::currentDateTime();
    this->ref_time=this->load_time;
}

RResource::~RResource(){
}

QString RResource::getName(){
    return this->name;
}

QString RResource::getFileName(){
    return this->file_name;
}

void *RResource::getResource(){
    return this->resource;
}

int RResource::getRefCount(){
    return this->ref_count;
}

bool RResource::increaseRefCount(){
    this->ref_count++;
    this->ref_time=QDateTime::currentDateTime();
    return true;
}

bool RResource::decreaseRefCount(){
    this->ref_count--;
    return this->ref_count>=0;
}
