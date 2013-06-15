#ifndef FMLIST_H
#define FMLIST_H

#include <QNetworkAccessManager>
#include <QLinkedList>
#include <QByteArrayData>
#include "fminfo.h"

class RListView;

class FMList : public QObject
{
    Q_OBJECT

private:
    void init();
    void parse();
    void loadFM();

public:
    FMList(QNetworkAccessManager* network_manager,RListView* view);
    ~FMList();

    void load();
    FMInfo* getFM(int index=0);

private:
    QNetworkAccessManager* network_manager;
    RListView* view;
    QNetworkRequest request;
    QNetworkReply* reply;
    QString html_string;
    QLinkedList<FMInfo*> fm_list;
    int loaded_count;

signals:
    void addFM(FMInfo* info);
    void FMListLoaded();
    void played(FMInfo* info);

private slots:
    void finish();
    void FMLoaded(FMInfo* info);
    void FMPlay(FMInfo* info);
};

#endif // FMLIST_H
