#ifndef FMINFO_H
#define FMINFO_H

#include <QString>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

class FMInfo : public QObject
{
    Q_OBJECT

private:
    void writeToFile(QByteArray &data);
    void getPicName();

public:
    FMInfo(QString name, QString id, QString pic_url);
    ~FMInfo();

    void load(QNetworkAccessManager* network_manager);
    void changeStatus(bool status);

public:
    QString name;
    QString id;
    QString pic_url;
    QString pic_name;

private:
    QNetworkRequest request;
    QNetworkReply* reply;
    bool is_loaded;
    bool is_playing;

signals:
    void loaded(FMInfo* info);
    void played(FMInfo* info);
    void statusChanged(bool status);

private slots:
    void loadFinish();

public slots:
    void play();
};

#endif // FMINFO_H
