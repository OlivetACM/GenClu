#pragma once
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QFile>

class MainWindow : public QWidget {

    Q_OBJECT

    public:
        // Constructor
        MainWindow(QWidget *parent = 0);
    
    private slots:
        void manual(QString id = NULL);
        void close();


    private:
        // Variables
        QLabel *key;
        bool concat;
        QString lastId;
        QFile currentFile;
        QMap<QString, QMap<QString, QString>> allMembers;
        QStringList attendance;
        //QFile memberFile;

        // Methods
        void keyPressEvent(QKeyEvent *event);
        void improperSwipe();
        void gatherIDs();

};
