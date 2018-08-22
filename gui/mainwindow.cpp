#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QDate>
#include <QDateTime>
#include <QDir>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QFont>
#include <QDebug>
#include <QDialog>
#include <QString>
#include <supplementary.h>
#include <mainwindow.h>
#include <badswipe.h>
#include <manualentries.h>
#include <previousevents.h>

MainWindow::MainWindow (QWidget *parent) : QWidget(parent) {
    setWindowTitle("Generic Club Tracker");
    concat = false;
    // Generate cosmetics
    QLabel *top = new QLabel("Please Begin Swiping to take Attendance");
    QFont topFont;
    topFont.setPointSize(32);
    top->setFont(topFont);
    // Generate Date
    QDate current = QDate::currentDate();
    QLabel *today = new QLabel("Current Date: " + current.toString("MMMM dd, yyyy"), this);
    QFont font;
    font.setPointSize(24);
    today->setFont(font);
    // Key pressed
    //key = new QLabel("", this);
    
    // Extra Widgets
    QWidget *buttons = new QWidget(this);
    QGridLayout *buttonLayout = new QGridLayout();
    buttons->setLayout(buttonLayout);
    
    hello = new QLabel("MARKED ATTENDEES APPEAR HERE", this);
    hello->setFont(font);
    
    // Buttons
    QPushButton *newOutputFile = new QPushButton("Change File", this);
    QPushButton *manual = new QPushButton("Manual Entry", this);
    QPushButton *finish = new QPushButton("Finished", this);
    buttonLayout->addWidget(newOutputFile, 0, 0);
    buttonLayout->addWidget(manual, 0, 1);
    buttonLayout->addWidget(finish, 0, 2);

    // Timer to fix garbage card input
    keyTimer = new QTimer(this);
    keyTimer->setSingleShot(true);

    // Slots
    connect(newOutputFile, SIGNAL(clicked()), this, SLOT(getAttendanceFilename()));
    connect(manual, SIGNAL(clicked()), this, SLOT(manual()));
    connect(finish, SIGNAL(clicked()), this, SLOT(close()));
    connect(keyTimer, SIGNAL(timeout()), this, SLOT(startAttendance()));
    // Small extra
    attendLabel = new QLabel("Writing To: ", this);
    attendLabel->setFont(font);
    // Generate Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(top, 1, Qt::AlignCenter);
    layout->addWidget(today, 1, Qt::AlignCenter);
    //layout->addWidget(key, Qt::AlignCenter);
    layout->addWidget(attendLabel, 1, Qt::AlignCenter);
    layout->addWidget(hello, 1, Qt::AlignRight);
    layout->addWidget(buttons, 1, Qt::AlignRight);

    setLayout(layout);
    //layout->setAlignment(Qt::AlignHCenter);
    // Startup the csvDB
    show();

    memberFile = "./members.csv";
    gatherIDs();
    getAttendanceFilename();
}

void MainWindow::close() {
    QApplication::quit();
}


void MainWindow::gatherIDs() {
    // Open a Members CSV
    qDebug() << "Loading in" << memberFile;
    allMembers = loadMembers(memberFile);
    qDebug() << allMembers;
    // Also open the file for writing
    //memberFile.setFileName("../members.csv");
    //memberFile.open(QIODevice::WriteOnly | QIODevice::Text);
}

void MainWindow::startAttendance() {
    QStringList keys = allMembers.keys();
    // Check good swipe
    if (!goodSwipe) {
        improperSwipe();
    }
    // Call manual Entry if not in users
    else if (!keys.contains(lastId)) {
        // Call Manual Entry
        manual(lastId);
    }
    // Then mark them as attended
    else {
        mark();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    // Only Fire when timer is off
    if (event->key() == Qt::Key_Semicolon) {
        goodSwipe = false;
        // Catches first input but not the rest
        if (!keyTimer->isActive()) {
            lastId = QString();
            concat = true;
            // 100ms should be enough time to capture card input
            keyTimer->start(400);
        }
    }
    else if (event->key() == Qt::Key_Question) {
        concat = false;
        goodSwipe = true;
        qDebug() << lastId;
    }
    else if (concat) {
        lastId.append(event->text());
    }
    else if (goodSwipe) {
        // Do nothing else
    }

    else {
        goodSwipe = false;
    }
    //qDebug() << lastId;
}

void MainWindow::improperSwipe() {
    concat = false;
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
            QStringList keys = allMembers.keys();
            if (!keys.contains(newMember["id"])) {
                QFileInfo csvInfo(memberFile);
                bool fileExists = csvInfo.exists() && csvInfo.isFile();
                QFile memberFile(&memberFile);
                memberFile.open(QIODevice::Append | QIODevice::Text);
                QTextStream memberStream(&memberFile);
                if (!fileExists) {
                    memberStream << "ID,Last Name,First Name" << "\n";
                }
                memberStream << newMember["id"] + "," +
                                newMember["last"] + "," + 
                                newMember["first"] << "\n";
                // Add to memory
                QMap<QString, QString> temp;
                temp["first"] = newMember["first"];
                temp["last"] = newMember["last"];
                temp["present"] = "false";
                allMembers[newMember["id"]] = temp;
                qDebug() << QString("Updated Members:\n") << allMembers;
                memberFile.close();
            }
            lastId = newMember["id"];
        }
    }
    delete manWindow;

    // Mark as attended
    mark();
}

void MainWindow::mark() {
    // Check if already marked
    if (allMembers[lastId]["present"] == "false") {
        hello->setText("Hello " + 
                allMembers[lastId]["first"] + " " +
                allMembers[lastId]["last"] + "!");
        allMembers[lastId]["present"] = "true";
        // Write to file -> Replace with 
        // https://github.com/jmcnamara/MSVCLibXlsxWriter
        if (markType == "csv") {
            QString filename = attendPath + attendFile + ".csv";
            QFileInfo csvInfo(filename);
            bool fileExists = csvInfo.exists() && csvInfo.isFile();
            qDebug() << "Writing to CSV{" << attendFile << ".csv}";
            QFile writeTo(filename);
            writeTo.open(QIODevice::Append | QIODevice::Text);
            QTextStream output(&writeTo);
            if (!fileExists) {
                // Write Categories
                output << "Last Name,First Name,ID" << "\n";
            }
            QString last = allMembers[lastId]["last"];
            QString first = allMembers[lastId]["first"];
            output << last + ","
                << first + ","
                << lastId
                << "\n";
            // Show popup confirming
            //
            writeTo.close();
        }
        else if (markType == "xlsx") {
            // Not yet implemented
        }
    }
    else {
        hello->setText("MEMBER ALREADY SWIPED");
        qDebug() << "Member ID: " << lastId << " already marked";
    }

}

void MainWindow::getAttendanceFilename() {
    // Pass Todays Date
    PreviousEvent *todaysEvent = new PreviousEvent(QDate::currentDate());
    int result = todaysEvent->exec();
    if (result) {
        attendFile = todaysEvent->getAttendanceFilename();
        markType = todaysEvent->getMarkType();
        attendLabel->setText("Writing To: " + attendFile + "." + markType);
        attendPath = todaysEvent->getFilePath();
        qDebug() << "Event file:" << attendFile << "selected!";
        delete todaysEvent;
    }
    if (attendFile.trimmed().isEmpty()) {
        exit(0);
    }
    else {
        resetMarked();
        QFile input(attendPath + "/" + attendFile + "." + markType);
        // If the file already exists
        if (input.exists()) {
            // loading old file
            // Make sure to up date the attendance record so it 
            // won't double mark people
            reMark();
        }
    }
}

void MainWindow::resetMarked() {
    QStringList keys = allMembers.keys();
    int len = keys.length();
    for (int i = 0; i < len; i++) {
        allMembers[keys.at(i)]["present"] = "false";
    }
}

void MainWindow::reMark() {
    if (markType == "csv") {
        // Read in new file
        QFile input(attendPath + "/" + attendFile + ".csv");
        input.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream readFrom(&input);
        QStringList members = readFrom.readAll().trimmed().split("\n");
        input.close();
        int len = members.length();
        qDebug() << "Previous Entries" << len;
        QStringList member;
        for (int i = 1; i < len; i++) {
            member = members.at(i).split(",");
            allMembers[member.at(2)]["present"] = "true";
        }
        qDebug() << "Attendance Updated for New File";
        qDebug() << allMembers;
    }
    hello->setText("");
}
int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow window;
    return app.exec();
}
