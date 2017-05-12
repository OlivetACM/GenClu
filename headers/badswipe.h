#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QDialog>

class badSwipe : public QDialog {

    Q_OBJECT

    public:
        // Constructor
        badSwipe(QWidget *parent = 0, Qt::WindowFlags f = 0);
};
