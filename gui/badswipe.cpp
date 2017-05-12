#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <badswipe.h>

badSwipe::badSwipe(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Bad Swipe Detected");
    // Generate layout
    QGridLayout *grid = new QGridLayout(this);
    // Generate buttons
    QLabel *warning = new QLabel("Bad swipe detected. \n Press Cancel to swipe again, or press Manual for manual entry.", this);
    QPushButton *cancel = new QPushButton("Cancel", this);
    QPushButton *manual = new QPushButton("Manual", this);
    // Put it all together
    grid->addWidget(warning, 0, 0, 2, 2);
    grid->addWidget(cancel, 3, 2);
    grid->addWidget(manual, 3, 1);
}
