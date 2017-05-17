#include <QWidget>
#include <QDialog>
#include <QDate>
#include <QDir>
#include <QRadioButton>
#include <QButtonGroup>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QString>
#include <QStringList>
#include <previousevents.h>

PreviousEvent::PreviousEvent(QDate today, QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f) {
    getEvents(today);
    // Information
    QLabel *info = new QLabel("PREVIOUS EVENTS FOR TODAY DETECTED!", this);
    QLabel *cate1 = new QLabel("Use (check one)", this);
    QLabel *cate2 = new QLabel("Set Option", this);

    // Two radio buttons
    radioGroup = new QButtonGroup(this);
    newEventRadio = new QRadioButton("New Event", this);
    previousEventRadio = new QRadioButton("Previous Event", this);

    radioGroup->addButton(newEventRadio, 0);
    radioGroup->addButton(previousEventRadio, 1);
    // A Combo box
    combo = new QComboBox(this);
    combo->addItems(allFiles);
    // A QLabel
    //QLabel newEventLabel = new QLabel(newFile, this);
    newEventEdit = new QLineEdit(this);
    newEventEdit->setPlaceholderText("No extension on name!");
    newEventEdit->setText(newFile);

    // Accept / Reject
    QPushButton *acceptButton = new QPushButton("Accept", this);
    QPushButton *cancel = new QPushButton("Cancel", this);
    connect(acceptButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()),  this, SLOT(reject()));

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(info, 0, 0, 1, 3);
    grid->addWidget(cate1, 1, 0);
    grid->addWidget(cate2, 1, 1, 1, 2);
    grid->addWidget(newEventRadio, 2, 0);
    grid->addWidget(newEventEdit, 2, 1, 1, 2);
    grid->addWidget(previousEventRadio, 3, 0);
    grid->addWidget(combo, 3, 1, 1, 2);
    grid->addWidget(acceptButton, 4, 1);
    grid->addWidget(cancel, 4, 2);
    setLayout(grid);
}

void PreviousEvent::getEvents(QDate today) {
    // Sets newFile and allFiles for the combo box situation
    current.setCurrent("./attendance/");
    QString todayStr = today.toString("yyy.MM.dd");
    if (!current.exists()) {
        current.setCurrent("./");
        current.mkdir("attendance");
    }
    current.setCurrent("./attendance/" + todayStr + "/");
    if (!current.exists()) {
        current.setCurrent("./attendance/");
        current.mkdir(todayStr);
        current.setCurrent("./attendance/" + todayStr + "/");
    }
    // Check For previous events here
    allFiles = current.entryList(QDir::Files);
    if (allFiles.isEmpty()) {
        newFile = "event1";
    }
    else {
        allFiles.sort();
        QStringList nameFilters;
        nameFilters << "events*.csv" << "events*.xlsx";
        QStringList genericEvents = current.entryList(
                nameFilters,
                QDir::Files);
        if (!genericEvents.isEmpty()) {
            genericEvents.sort();
            QString lastEvent = genericEvents.at(genericEvents.length() - 1);
            QStringList lastSplit = lastEvent.split(".");
            lastEvent = lastSplit.at(0);
            int len = lastEvent.length();
            // Event is 5 letters long
            lastEvent = lastEvent.mid(6, len - 5 - 1);
            lastEvent = lastEvent.toInt() + 1;
            newFile = lastEvent;
        }
        else {
            newFile = "event1";
        }
    }
}

QString PreviousEvent::getAttendanceFilename() {
    if (newEventRadio->isChecked()) {
        QString text = newEventEdit->text();
        if (!text.isEmpty()) {
            return text;
        }
        else {
            return newFile;
        }
    }
    else {
        if (!allFiles.isEmpty()) {
            return allFiles.at(combo->currentIndex());
        }
        else {
            return newFile;
        }
    
    }

}
