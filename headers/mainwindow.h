#pragma once
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QFile>
#include <QTimer>

class MainWindow : public QWidget {

    Q_OBJECT

    public:
        // Constructor
        MainWindow(QWidget *parent = 0);
    
    private slots:
        void manual(QString id = NULL);
        void close();
        // Timer to soak extra input
        void startAttendance();


    private:
        // Variables
        QLabel *key;
        bool concat;
        QString lastId;
        QFile currentFile;
        QMap<QString, QMap<QString, QString>> allMembers;
        QStringList attendance;
        
        QTimer *keyTimer = nullptr;
        //QFile memberFile;

        // Methods
        void keyPressEvent(QKeyEvent *event);
        void improperSwipe();
        void gatherIDs();

};
