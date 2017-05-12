CONFIG += qt debug console
QT += widgets
INCLUDEPATH += headers/ cpp/ gui/
HEADERS +=  headers/mainwindow.h \
            headers/badswipe.h
SOURCES +=  gui/mainwindow.cpp \
            gui/badswipe.cpp
# All other includes go here
