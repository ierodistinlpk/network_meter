# -------------------------------------------------
# Project created by QtCreator 2009-05-31T23:04:49
# -------------------------------------------------
QT += opengl \
    sql
TARGET = test
TEMPLATE = app
SOURCES += main.cpp \
    testwindow.cpp \
    histogram_item.cpp \
    points_item.cpp
HEADERS += testwindow.h \
    constants.h \
    histogram_item.h \
    points_item.h
FORMS += testwindow.ui \
    help.ui
LIBS += -L/usr/lib \
    -lqwt-qt4
