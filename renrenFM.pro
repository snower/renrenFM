#-------------------------------------------------
#
# Project created by QtCreator 2013-05-23T20:10:35
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = renrenFM
TEMPLATE = app


SOURCES += main.cpp\
        ui/window.cpp \
    ui/rbutton.cpp \
    ui/rbuttonstatusconfig.cpp \
    ui/rslipfence.cpp \
    ui/rfence.cpp \
    ui/rlistview.cpp \
    ui/ritemview.cpp \
    ui/rview.cpp \
    ui/rplayer.cpp \
    resource/rresource.cpp \
    ui/rcdplayer.cpp \
    ui/rprogressbar.cpp \
    ui/rvolume.cpp \
    ui/rtimershaft.cpp \
    renrenfm.cpp \
    resource/rresourcecache.cpp \
    player/fmplayer.cpp \
    player/fminfo.cpp \
    player/playinfo.cpp \
    player/playlist.cpp \
    player/fmlist.cpp \
    player/json.cpp

HEADERS  += ui/window.h \
    ui/rbutton.h \
    ui/rbuttonstatusconfig.h \
    ui/rslipfence.h \
    ui/rfence.h \
    ui/rlistview.h \
    ui/ritemview.h \
    ui/rview.h \
    ui/rplayer.h \
    resource/rresource.h \
    ui/rcdplayer.h \
    ui/rprogressbar.h \
    ui/rvolume.h \
    ui/rtimershaft.h \
    renrenfm.h \
    resource/rresourcecache.h \
    player/fmplayer.h \
    player/fminfo.h \
    player/playinfo.h \
    player/playlist.h \
    player/fmlist.h \
    player/json.h

FORMS    += ui/window.ui
