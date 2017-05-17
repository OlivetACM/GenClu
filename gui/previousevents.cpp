#include <QDialog>
#include <QDir>
#include <previousevents.h>

PreviousEvent::PreviousEvent(QDate today, QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f) {
    // Two radio buttons
    // A Combo box
    // A QLabel

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
        current.mkdir(todaystr);
        current.setCurrent("./attendance/" + todayStr + "/");
    }
    // Check For previous events here
    allFiles = current.entryList(filter = QDir::Files);
    if (allFiles.isEmpty()) {
        newFile = "event1";
    }
    else {
        allFiles.sort();
        QStringList nameFilters;
        nameFilters << "events*.csv" << "events*.xlsx";
        QStringList genericEvents = current.entryList(
                nameFilter = nameFilters,
                filter = QDir::Files);
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
