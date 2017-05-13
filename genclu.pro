CONFIG += qt debug console
QT += widgets
INCLUDEPATH += headers/ cpp/ gui/
HEADERS +=  headers/mainwindow.h \
            headers/badswipe.h \
            headers/manualentries.h \
            headers/supplementary.h
SOURCES +=  gui/mainwindow.cpp \
            gui/badswipe.cpp \
            gui/manualentries.cpp \
            helpers/supplementary.cpp
# All other includes go here
