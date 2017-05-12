#pragma once
#include <QApplication>
#include <QWidget>
#include <QLabel>

class MainWindow : public QWidget {

    Q_OBJECT

    public:
        // Constructor
        MainWindow(QWidget *parent = 0);
    
    private slots:
        void manualEntry();
        void close();


    private:
        // Variables
        QLabel *key;
        bool concat;
        QString lastId;
        // Methods
        void keyPressEvent(QKeyEvent *event);
        void improperSwipe();

};
