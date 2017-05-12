#pragma once
#include <QApplication>
#include <QWidget>
#include <QLabel>

class MainWindow : public QWidget {

    Q_OBJECT

    public:
        // Constructor
        MainWindow(QWidget *parent = 0);

    private:
        // Variables
        QLabel *key;

        // Methods
        void keyPressEvent(QKeyEvent *event);

};
