#pragma once
#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

class doubleCheck : public QDialog {
    Q_OBJECT

    public:
        doubleCheck(QString fname, QString lname, QString ID, QWidget *parent = 0, Qt::WindowFlags f = 0);

    private:

};
