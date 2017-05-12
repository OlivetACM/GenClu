#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <manualentries.h>

manualEntry::manualEntry(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f){
    setWindowTitle("Manual Entry");
    
    // Generate Layout
    QGridLayout *grid = new QGridLayout(this);

    // Generate input and selection boxes
    QLabel *line1 = new QLabel("First Name: ", this);
    QLineEdit *firstName = new QLineEdit;
    firstName->setPlaceholderText("First name...");

    QLabel *line2 = new QLabel("Last Name: ", this);
    QLineEdit *lastName = new QLineEdit;
    lastName->setPlaceholderText("Last name...");
    
    QLabel *line3 = new QLabel("Student ID: ", this);
    QLineEdit *studentID = new QLineEdit;
    studentID->setPlaceholderText("Student ID...");

    QPushButton *cancel = new QPushButton("Cancel", this);
    QPushButton *confirm = new QPushButton("Confirm", this);
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(confirm, SIGNAL(clicked()), this, SLOT(accept()));
    
    // Tying it all together
    grid->addWidget(line1, 0, 0);
    grid->addWidget(firstName, 0, 1, 0, 2);

    grid->addWidget(line2, 1, 0);
    grid->addWidget(lastName, 1, 1, 1, 2);
    
    grid->addWidget(line3, 2, 0);
    grid->addWidget(studentID, 2, 1, 2, 2);
    
    grid->addWidget(confirm, 3, 1);
    grid->addWidget(cancel, 3, 2);

    setLayout(grid);
}
