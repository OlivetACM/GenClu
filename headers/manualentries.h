#pragma once
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

class manualEntry : public QDialog {
    Q_OBJECT

    public:
        manualEntry(QWidget *parent = 0, Qt::WindowFlags f = 0);
        manualEntry(QString id, QWidget *parent = 0, Qt::WindowFlags f = 0);

        // Methods
        QMap<QString, QString> data();

    public slots:
        void accept() override;

    private:
        QLineEdit *firstName;
        QLineEdit *lastName;
        QLineEdit *studentID;

        // Methods
        void initLayout(QGridLayout *grid);

};
