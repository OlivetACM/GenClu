#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMap>
#include <QString>
#include <manualentries.h>

manualEntry::manualEntry(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f){
    QGridLayout *grid = new QGridLayout(this);
    initLayout(grid);
}

manualEntry::manualEntry(QString id, QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f){
    QGridLayout *grid = new QGridLayout(this);
    initLayout(grid);
    // Set the label to non editable
    studentID->setReadOnly(true);
    studentID->setText(id);
}

void manualEntry::initLayout(QGridLayout *grid) {
    setWindowTitle("Manual Entry");
    
    // Generate Layout

    // Generate input and selection boxes
    QLabel *line1 = new QLabel("First Name: ", this);
    firstName = new QLineEdit(this);
    firstName->setPlaceholderText("First name...");

    QLabel *line2 = new QLabel("Last Name: ", this);
    lastName = new QLineEdit(this);
    lastName->setPlaceholderText("Last name...");
    
    QLabel *line3 = new QLabel("Student ID: ", this);
    studentID = new QLineEdit(this);
    studentID->setPlaceholderText("Student ID...");

    QPushButton *cancel = new QPushButton("Cancel", this);
    QPushButton *confirm = new QPushButton("Confirm", this);
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(confirm, SIGNAL(clicked()), this, SLOT(accept()));
    
    // Tying it all together
    grid->addWidget(line1, 0, 0);
    grid->addWidget(firstName, 0, 1, 1, -1);

    grid->addWidget(line2, 1, 0);
    grid->addWidget(lastName, 1, 1, 1, -1);
    
    grid->addWidget(line3, 2, 0);
    grid->addWidget(studentID, 2, 1, 1, -1);
    
    grid->addWidget(confirm, 3, 1);
    grid->addWidget(cancel, 3, 2);

    setLayout(grid);

}


QMap<QString, QString> manualEntry::data() {
    QMap<QString, QString> results;
    results["first"] = firstName->text();
    results["last"] = lastName->text();
    results["id"] = studentID->text();
    return results;
}
