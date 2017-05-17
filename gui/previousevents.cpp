#include <QDialog>
#include <QDir>
#include <previousevents.h>

PreviousEvent::PreviousEvent(QDate today, QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f) {


}

void PreviousEvent::getEvents() {
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
}
