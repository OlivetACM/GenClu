#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QDate>
#include <QDateTime>
#include <QVBoxLayout>
#include <mainwindow.h>

MainWindow::MainWindow (QWidget *parent) : QWidget(parent) {
    setWindowTitle("Generic Club Tracker");
    // Generate Date
    QDate current = QDate::currentDate();
    QLabel *today = new QLabel(current.toString("MMMM dd, yyyy"), this);
    // Key pressed
    key = new QLabel("", this);

    // Generate Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(today);
    layout->addWidget(key);
    setLayout(layout);
    show();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    key->setText(event->text());
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow window;
    return app.exec();
}
