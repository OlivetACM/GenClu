#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <doublecheck.h>

doubleCheck::doubleCheck(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f) {
    setWindowTitle("Confirm Action");

    // Generate Layout
    QGridLayout *grid = new QGridLayout(this);
    QLabel *warning = new QLabel("Are you sure you want to do this?", this);
    
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
