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
        void getAttendanceFilename();


    private:
        // Variables
        QLabel *key;
        bool concat;
        QString lastId;
        QString memberFile;
        QString attendFile;
        QString attendPath;
        QMap<QString, QMap<QString, QString>> allMembers;
        QStringList attendance;
        QLabel *attendLabel;
        
        QTimer *keyTimer = nullptr;
        bool goodSwipe = false;
        QString markType = "csv";
        QLabel *hello;
        //QFile memberFile;

        // Methods
        void keyPressEvent(QKeyEvent *event);
        void improperSwipe();
        void gatherIDs();
        void mark();
        void resetMarked();
        void reMark();



};
