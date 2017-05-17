#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QDate>
#include <QDateTime>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QFont>
#include <QDebug>
#include <QDialog>
#include <QThread>
#include <supplementary.h>
#include <mainwindow.h>
#include <badswipe.h>
#include <manualentries.h>

MainWindow::MainWindow (QWidget *parent) : QWidget(parent) {
    setWindowTitle("Generic Club Tracker");
    concat = false;
    // Generate cosmetics
    QLabel *top = new QLabel("Please Begin Swipping to take Attendance");
    QFont topFont;
    topFont.setPointSize(32);
    top->setFont(topFont);
    // Generate Date
    QDate current = QDate::currentDate();
    QLabel *today = new QLabel("Current Date\n" + current.toString("MMMM dd, yyyy"), this);
    QFont font;
    font.setPointSize(24);
    today->setFont(font);
    // Key pressed
    //key = new QLabel("", this);
    
    // Extra Widgets
    QWidget *buttons = new QWidget(this);
    QGridLayout *buttonLayout = new QGridLayout();
    buttons->setLayout(buttonLayout);
    // Buttons
    QPushButton *manual = new QPushButton("Manual Entry", this);
    QPushButton *finish = new QPushButton("Finished", this);
    buttonLayout->addWidget(manual, 0, 0);
    buttonLayout->addWidget(finish, 0, 1);

    // Timer to fix garbage card input
    keyTimer = new QTimer(this);
    // Preppin'
    keyTimer->setSingleShot(true);

    // Slots
    connect(manual, SIGNAL(clicked()), this, SLOT(manual()));
    connect(finish, SIGNAL(clicked()), this, SLOT(close()));
    connect(keyTimer, SIGNAL(timeout()), this, SLOT(startAttendance()));
    // Generate Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(top, 1, Qt::AlignCenter);
    layout->addWidget(today, 1, Qt::AlignCenter);
    //layout->addWidget(key, Qt::AlignCenter);
    layout->addWidget(buttons, 1, Qt::AlignRight);
    setLayout(layout);
    //layout->setAlignment(Qt::AlignHCenter);
    // Startup the csvDB
    gatherIDs();
    show();
}

void MainWindow::gatherIDs() {
    // Open a Members CSV
    allMembers = loadMembers("../members.csv");
    qDebug() << allMembers;
    // Also open the file for writing
    //memberFile.setFileName("../members.csv");
    //memberFile.open(QIODevice::WriteOnly | QIODevice::Text);
}

void MainWindow::close() {

}

void MainWindow::startAttendance() {
    // Call manual Entry if not in users
    QStringList keys = allMembers.keys();
    if (!keys.contains(lastId)) {
        // Call Manual Entry
        manual(lastId);
    }
    // Then mark them as attended
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    // Only Fire when timer is off
    if (event->key() == Qt::Key_Semicolon) {
        // Catches first input but not the rest
        if (!keyTimer->isActive()) {
            lastId = QString();
            concat = true;
            // 100ms should be enough time to capture card input
            keyTimer->start(100);
        }
    }
    else if (event->key() == Qt::Key_Question) {
        concat = false;
    }
    //else if (event->key() == Qt::Key_Return) {
        // Call manual Entry if not in users
        //QStringList keys = allMembers.keys();
        //if (!keys.contains(lastId)) {
            // Brief pause to stop garbage input from the card
            //QThread::msleep(1000);
            // Call Manual Entry
            //manual(lastId);
        //}
        // Then mark them as attended
    //}
    else if (concat) {
        lastId.append(event->text());
    }
    qDebug() << lastId;
}

void MainWindow::improperSwipe() {
    badSwipe *doManual = new badSwipe(this);
    //doManual->show();
    int result = doManual->exec();
    delete doManual;
    if (result) {
        // Summon Manual Entry Window
        manual();
    }

}

void MainWindow::manual(QString id) {
    manualEntry *manWindow = nullptr;
    if (id != NULL) {
        manWindow = new manualEntry(id, this);
    }
    else {
        manWindow = new manualEntry(this);
    }
    int result = manWindow->exec();
    if (result) {
        // Gather results
        QMap<QString, QString> newMember = manWindow->data();
        // Write to File
        if (!newMember["id"].trimmed().isEmpty() && 
                !newMember["first"].trimmed().isEmpty() &&
                !newMember["last"].trimmed().isEmpty()) {
            QFile memberFile("../members.csv");
            memberFile.open(QIODevice::Append | QIODevice::Text);
            QTextStream memberStream(&memberFile);
            memberStream << newMember["id"] + "," +
                            newMember["last"] + "," + 
                            newMember["first"] << "\n";
            // Add to memory
            QMap<QString, QString> temp;
            temp["first"] = newMember["first"];
            temp["last"] = newMember["last"];
            allMembers[newMember["id"]] = temp;

            qDebug() << QString("Updated Members:\n") << allMembers;
            memberFile.close();
        }
    }
    delete manWindow;
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow window;
    return app.exec();
}
