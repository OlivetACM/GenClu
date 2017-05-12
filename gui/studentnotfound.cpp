#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <studentnotfound.h>

doubleCheck::doubleCheck(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f) {
    setWindowTitle("New Student");

    // Generate Layout
    QGridLayout *grid = new QGridLayout(this);
    QLabel *notification = new QLabel("This student has not yet swiped their ID.\nClick 'add' to add them to your local list of\nmembers or click 'cancel' to ignore them.", this);
    
    // Generate Buttons
    QPushButton *add = new QPushButton("Add", this);
    QPushButton *cancel = new QPushButton("Cancel", this);
    connect(add, SIGNAL(clicked()), this, SLOT(reject()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(accept()));

    // Bring it all together
    grid->addWidget(notification, 0, 0, 2, 2);
    grid->addWidget(cancel, 3, 2);
    grid->addWidget(add, 3, 1);

    setLayout(grid);
}
