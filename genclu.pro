CONFIG += qt debug_and_release
QT += widgets
INCLUDEPATH += headers/ cpp/ gui/
HEADERS +=  headers/mainwindow.h \
            headers/badswipe.h \
            headers/manualentries.h \
            headers/supplementary.h \
            headers/previousevents.h \
            headers/doublecheck.h
SOURCES +=  gui/mainwindow.cpp \
            gui/badswipe.cpp \
            gui/manualentries.cpp \
            helpers/supplementary.cpp \
            gui/previousevents.cpp \
            gui/doublecheck.cpp
# All other includes go here
