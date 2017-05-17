#include <QDialog>
#include <QDir>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QDate>
#include <QWidget>
#include <QComboBox>
#include <QString>
#include <QStringList>

class PreviousEvent : public QDialog {
    
    Q_OBJECT

    public:
        PreviousEvent(QDate today, QWidget *parent = 0, Qt::WindowFlags f = 0);
        QString getAttendanceFilename();
    private:
        void getEvents(QDate today);
        // 
        QDir current;
        QStringList allFiles;
        QString newFile;

        QComboBox *combo;
        QButtonGroup *radioGroup;
        QRadioButton *newEventRadio;
        QRadioButton *previousEventRadio;
        QLineEdit *newEventEdit;

};
