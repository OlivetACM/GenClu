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
        QString memberFile;
        QString attendFile;
        QMap<QString, QMap<QString, QString>> allMembers;
        QStringList attendance;
        
        QTimer *keyTimer = nullptr;
        bool goodSwipe = false;
        QString markType = "csv";
        //QFile memberFile;

        // Methods
        void getAttendanceFilename();
        void keyPressEvent(QKeyEvent *event);
        void improperSwipe();
        void gatherIDs();
        void mark();


};
