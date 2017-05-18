#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <doublecheck.h>

//take fname, lname, ID
doubleCheck::doubleCheck(QString fname, QString lname, QString ID, QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f) {
    setWindowTitle("Confirm Action");

    // Generate Layout
    QGridLayout *grid = new QGridLayout(this);
    QString testing = "Are you sure you want to do this?\nFirst Name: %1\nLast Name: %2\nStudent ID: %3";
    testing = testing.arg(fname).arg(lname).arg(ID);

        /* +
            "First name: " + fname + "\n" +
            "Last name: " + lname + "\n" +
            "Student ID: " + ID; */
    QLabel *warning = new QLabel(testing, this);

    // Generate Buttons
    QPushButton *cancel = new QPushButton("Cancel", this);
    QPushButton *confirm = new QPushButton("Confirm", this);
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(confirm, SIGNAL(clicked()), this, SLOT(accept()));

    // Bring it all together
    grid->addWidget(warning, 0, 0, 1, 2);    
    grid->addWidget(cancel, 2, 2);
    grid->addWidget(confirm, 2, 1);
    setLayout(grid);
    
}
