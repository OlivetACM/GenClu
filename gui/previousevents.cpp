#include <QWidget>
#include <QDebug>
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
#include <QFont>
#include <previousevents.h>

PreviousEvent::PreviousEvent(QDate today, QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f) {
    getEvents(today);
    // Information
    //QLabel *info = new QLabel("PREVIOUS EVENTS FOR TODAY DETECTED!", this);
    QLabel *info = new QLabel("Pick a new or old event!", this);
    QFont font;
    font.setPointSize(20);
    info->setFont(font);
    //setWindowTitle("Choose an old event or make a new one!");
    QLabel *cate1 = new QLabel("Use (check one)", this);
    QLabel *cate2 = new QLabel("Set Option", this);

    // Two radio buttons
    radioGroup1 = new QButtonGroup(this);
    newEventRadio = new QRadioButton("New Event", this);
    previousEventRadio = new QRadioButton("Previous Event", this);

    newEventRadio->setChecked(true);

    if (allFiles.isEmpty()) {
        previousEventRadio->setCheckable(false);
    }

    radioGroup1->addButton(newEventRadio, 0);
    radioGroup1->addButton(previousEventRadio, 1);
    // A Combo box
    combo = new QComboBox(this);
    combo->addItems(allFiles);
    // A QLabel
    //QLabel newEventLabel = new QLabel(newFile, this);
    newEventEdit = new QLineEdit(this);
    newEventEdit->setPlaceholderText("No extension on name!");
    newEventEdit->setText(newFile);

    // Mark Type
    QLabel *formatLabel = new QLabel("File Format", this);
    QButtonGroup *radioGroup2 = new QButtonGroup(this);
    csvButton = new QRadioButton("CSV Table", this);
    csvButton->setChecked(true);
    xlsxButton = new QRadioButton("Excel File", this);

    radioGroup2->addButton(csvButton);
    radioGroup2->addButton(xlsxButton);
    // Not yet implemented
    xlsxButton->setCheckable(false);

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
    grid->addWidget(formatLabel, 3, 0);
    grid->addWidget(csvButton, 3, 1);
    grid->addWidget(xlsxButton, 3, 2);
    // Filler
    QLabel *filler = new QLabel("", this);
    grid->addWidget(filler, 4, 0, 1, 3);
    grid->addWidget(previousEventRadio, 5, 0);
    grid->addWidget(combo, 5, 1, 1, 2);
    grid->addWidget(acceptButton, 6, 1);
    grid->addWidget(cancel, 6, 2);
    setLayout(grid);
}

void PreviousEvent::getEvents(QDate today) {
    // Sets newFile and allFiles for the combo box situation
    current.setPath("./attendance/");
    QString todayStr = today.toString("yyyy.MM.dd");
    if (!current.exists()) {
        current.setPath("./");
        current.mkdir("attendance");
    }
    current.setPath("./attendance/" + todayStr + "/");
    if (!current.exists()) {
        current.setPath("./attendance/");
        current.mkdir(todayStr);
        current.setPath("./attendance/" + todayStr + "/");
    }
    // Check For previous events here
    qDebug() << "Current Event Directory: " << current.absolutePath();
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
            lastEvent = lastEvent.mid(6, len - 5);
            lastEvent = lastEvent.toInt() + 1;
            newFile = "event" + lastEvent;
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
    }
    else {
        if (!allFiles.isEmpty()) {
            // setMarkType button
            QStringList filename = allFiles.at(combo->currentIndex()).split(".");
            if  (filename.at(1) == "csv") {
                csvButton->setChecked(true);
            }
            else {
                xlsxButton->setChecked(true);
            }
            return filename.at(0);
        }
    }
    return newFile;

}

QString PreviousEvent::getFilePath() {
    return current.absolutePath() + "/";
}

QString PreviousEvent::getMarkType() {
    if (csvButton->isChecked()) {
        return "csv";
    }
    else {
        return "xlsx";
    }
}
