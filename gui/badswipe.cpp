#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QDialog>
#include <badswipe.h>

badSwipe::badSwipe(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f) {
//badSwipe::badSwipe(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Bad Swipe Detected");
    // Generate layout
    QGridLayout *grid = new QGridLayout(this);
    // Generate buttons
    QLabel *warning = new QLabel("Bad swipe detected. \n Press Cancel to swipe again, or press Manual for manual entry.", this);
    QPushButton *cancel = new QPushButton("Cancel", this);
    QPushButton *manual = new QPushButton("Manual", this);
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(manual, SIGNAL(clicked()), this, SLOT(accept()));

    // Put it all together
    grid->addWidget(warning, 0, 0, 2, 2);
    grid->addWidget(cancel, 3, 2);
    grid->addWidget(manual, 3, 1);

    setLayout(grid);

}
